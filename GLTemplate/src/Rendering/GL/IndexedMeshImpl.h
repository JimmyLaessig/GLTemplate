#pragma once

#include "Rendering/IndexedMesh.h"
#include "Rendering/GL/OpenGL.h"

//#include "Rendering/GL/GLTypes.h"
#include <optional>
 
namespace Rendering
{
namespace GL
{
class ContextImpl;
class BufferImpl;
class ShaderProgramImpl;


class IndexedMeshImpl : public Rendering::IIndexedMesh
{

private:

	IndexedMeshImpl(std::shared_ptr<ContextImpl> ctx);

public: 

	using Ptr = std::shared_ptr<IndexedMeshImpl>;


	~IndexedMeshImpl();


	static IndexedMeshImpl::Ptr create(std::shared_ptr<ContextImpl> context, const IIndexedMesh::Config& config);


	std::shared_ptr<ContextImpl> getContextImpl();


	PrimitiveType getPrimitiveType() const;


	size_t getNumIndices() const;


	bool bind(const std::vector<AttributeSemantic>& atrributes);


	void executeDrawCommand();

private: 

	// Gets or create  VAO for the specific attribute combination
	std::optional<GLuint> getOrCreateVAO(const std::vector<AttributeSemantic>& attributes);

	// Holds a VAO handle for each unique attribute signature combination
	std::unordered_map<size_t, GLuint> mVAOHandles;

	PrimitiveType mPrimitiveType;

	std::shared_ptr<BufferImpl> mIndexBuffer;

	std::unordered_map<std::string, std::shared_ptr<BufferImpl>> mAttributeBuffers;
};
}
}