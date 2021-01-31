#include "Rendering/GL/IndexedMeshImpl.h"

#include "Rendering/GL/ContextImpl.h"
#include "Rendering/GL/BufferImpl.h"

#include "Rendering/GL/internal/GLTypes.h"
#include "Rendering/Util.h"
#include <sstream>
#include <algorithm>
#include <iostream>

namespace Rendering
{
namespace GL
{

IndexedMeshImpl::IndexedMeshImpl(ContextImpl::Ptr ctx) :
	Rendering::IIndexedMesh(ctx)
{}


IndexedMeshImpl::~IndexedMeshImpl()
{
	for (auto& [_, vao] : mVAOHandles)
	{
		glDeleteVertexArrays(1, &vao);
	}
}


std::shared_ptr<IndexedMeshImpl>
IndexedMeshImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, const IIndexedMesh::Config& config)
{
	assert(context);
	if (config.indexBuffer) assert(context == config.indexBuffer->getContext());
	for (auto& [_, buffer] : config.vertexBuffers) { assert(context == buffer->getContext()); }

	IndexedMeshImpl::Ptr mesh(new IndexedMeshImpl(context));

	mesh->mIndexBuffer		= std::static_pointer_cast<BufferImpl>(config.indexBuffer);
	mesh->mPrimitiveType	= config.primitiveType;
	
	for (auto& [name, buffer] : config.vertexBuffers)
	{
		mesh->mAttributeBuffers[name] = std::static_pointer_cast<BufferImpl>(buffer);
	}
	
	return mesh;
}


std::shared_ptr<ContextImpl> 
IndexedMeshImpl::getContextImpl()
{
	return std::shared_ptr<ContextImpl>();
}


PrimitiveType 
IndexedMeshImpl::getPrimitiveType() const
{
	return mPrimitiveType;
}


size_t 
IndexedMeshImpl::getNumIndices() const
{
	return mIndexBuffer->size();
}


bool 
IndexedMeshImpl::bind(const std::vector<AttributeSemantic>& atrributes)
{
	if (auto vao = getOrCreateVAO(atrributes))
	{
		glBindVertexArray(*vao);
		return true;
	}
	return false;
}


void 
IndexedMeshImpl::executeDrawCommand()
{
	if (mIndexBuffer)
	{
		auto indexType	= getDataType(mIndexBuffer->getAttributeFormat());
		GLenum mode		= PrimitiveType2GLenum(mPrimitiveType);
		GLenum type		= DataType2GLenum(getDataType(mIndexBuffer->getAttributeFormat()));
		glDrawElements(mode, mIndexBuffer->size(), type, 0);
	}
}


std::optional<GLuint>
IndexedMeshImpl::getOrCreateVAO(const std::vector<AttributeSemantic>& attributes)
{
	// Computes a unique hash for the attribute semantic for which a vao is created
	auto calculateHash = [](const auto& attributes)
	{
		std::stringstream s;
		for (auto& attribute : attributes)
		{
			s << attribute.name << "_" << attribute.location << "_" << enumToString(attribute.format) << "_";
		}
		return std::hash<std::string>()(s.str());
	};
	
	auto key = calculateHash(attributes);
	// A VAO for this attribute signature was already created
	if (mVAOHandles.count(key) > 0)
	{
		return mVAOHandles[key];
	}

	// Create a custom VAO for this specific attribute signature, if no vao has been created previously
	// Determine if the mesh contains the correct vertex attribute buffers.
	// A semantic links to a vertex buffer if they share the same name and have the same attribute type
	bool isSemanticMatch = std::all_of(attributes.begin(), attributes.end(), [&](const auto& attr)
	{
		auto itr = std::find_if(mAttributeBuffers.begin(), mAttributeBuffers.end(), [&](auto& pair)
		{
			return pair.first == attr.name && pair.second->getAttributeFormat() == attr.format;
		});
		if (itr == mAttributeBuffers.end())
		{
			// TODO LOG
			std::cout << "IndexedMesh contains no attribute '"<< attr.name <<"' of type "<< enumToString(attr.format) << ". " << std::endl;
			return false;
		}
		return true;
	});
	// The attribute signature does not match the meshes vertex attributes
	if (!isSemanticMatch)
	{
		// TODO LOG
		return {};
	}

	// Create a VAO and bind the index buffer and attribute buffers to it
	GLuint vaoHandle;
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	if (mIndexBuffer)
	{
		mIndexBuffer->bind();
	}

	for (auto& attr : attributes)
	{
		auto buffer = mAttributeBuffers[attr.name];
		buffer->bind();
		buffer->setAttributePointer(attr.location);
	}

	glBindVertexArray(0);

	mVAOHandles[key] = vaoHandle;

	return vaoHandle;
}
}
}