#include "Rendering/GL/GLIndexedGeometry.h"
#include "Rendering/GL/GLTypeConversion.h"
#include "Components/IndexedGeometry.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>
#include <optional>



GLIndexedGeometry::GLIndexedGeometry(const IndexedGeometry* geometry)
	: IBackendIndexedGeometry(geometry)
{
	markOutdated();
}

GLIndexedGeometry::~GLIndexedGeometry()
{
	freeGpuMemory();
}


void GLIndexedGeometry::freeGpuMemoryImpl()
{
	// Delete previously allocated buffers
	glDeleteBuffers((GLsizei)VBOs.size(), VBOs.data());
	glDeleteVertexArrays(1, &VAO);
}


template<class VectorType>
GLuint createVertexBufferObject(const std::vector<VectorType>& vertexData, const std::optional<std::tuple<GLuint, GLuint>> vao_and_attributeIndex = {})
{
	auto type			= GLTypeConversion::toGLDataType<decltype(VectorType().x)>();
	auto numVertices	= vertexData.size();
	auto numBytes		= sizeof(VectorType);
	auto numChannels	= VectorType::length();

	// Bind vao and setup vertex attribute pointer
	if (vao_and_attributeIndex)
	{
		auto[vao, atributeIndex] = *vao_and_attributeIndex;
		glBindVertexArray(vao);
		
	}

	GLuint handle = 0;
	glGenBuffers(1u, &handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, numVertices * numBytes, &vertexData[0], GL_STATIC_DRAW);

	// Unbind VAO
	if (vao_and_attributeIndex)
	{
		auto[vao, atributeIndex] = *vao_and_attributeIndex;
		glEnableVertexAttribArray(atributeIndex);
		glVertexAttribPointer(atributeIndex, numChannels, type, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return handle;
}


GLuint createIndexBufferObject(const std::vector<unsigned int>& indices, std::optional<GLuint> vao = {})
{	
	if (vao)
	{
		glBindVertexArray(vao.value());
	}

	// Number of Indices
	auto numIndices = indices.size();

	GLuint handle = 0;
	glGenBuffers(1u, &handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	// Unbind VAO
	if (vao)
	{
		glBindVertexArray(0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return handle;
}


void GLIndexedGeometry::updateGpuMemoryImpl()
{
	freeGpuMemoryImpl();

	if (glGetError() != GL_NO_ERROR)
	{
		std::cout << "error" << std::endl;
	}

	auto& vertexData = geometry->getVertexData();

	auto numVertices = vertexData.positions.size();
	auto bufferIndex = 0u;

	// Generate OpenGL Vertex Array
	glGenVertexArrays(1, &VAO);
	if (glGetError() != GL_NO_ERROR)
	{
		std::cout << "error" << std::endl;
	}
	glBindVertexArray(VAO);
	if (glGetError() != GL_NO_ERROR)
	{
		std::cout << "error" << std::endl;
	}
		
	// Positions	= 0
	// Normals		= 1
	// Tangents		= 2
	// Bitangents	= 3
	// Colors		= 4
	// UVs			= 5..
	// Indices		= Last
	// Generate OpenGL Buffers
	VBOs.reserve(6 + vertexData.uvs.size());
	// Position Buffer
	VBOs.push_back(createVertexBufferObject(vertexData.positions, std::make_tuple(VAO, bufferIndex++)));
	// Normal Buffer
	VBOs.push_back(createVertexBufferObject(vertexData.normals, std::make_tuple(VAO, bufferIndex++)));
	// Tangent Buffer
	VBOs.push_back(createVertexBufferObject(vertexData.tangents, std::make_tuple(VAO, bufferIndex++)));
	// Bitangent Buffer
	VBOs.push_back(createVertexBufferObject(vertexData.bitangents, std::make_tuple(VAO, bufferIndex++)));
	// Fill Color Buffer
	VBOs.push_back(createVertexBufferObject(vertexData.colors, std::make_tuple(VAO, bufferIndex++)));
	// Fill UV Buffer(s)
	for (auto& uvs : vertexData.uvs)
	{
		VBOs.push_back(createVertexBufferObject(uvs, std::make_tuple(VAO, bufferIndex++)));
	}
	
	// Fill Index Buffer
	VBOs.push_back(createIndexBufferObject(vertexData.indices, VAO));


	glBindVertexArray(0);
	if (glGetError() != GL_NO_ERROR)
	{
		std::cout << "error" << std::endl;
	}
}


GLuint GLIndexedGeometry::getVertexArrayObject() const
{
	return VAO;
}