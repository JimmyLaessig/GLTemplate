#include "Mesh.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>
#include <optional>
#include "GL/glew.h"


SubMeshVertexData::SubMeshVertexData(const SubMeshVertexData & other) :
	positions(other.positions),
	normals(other.normals),
	tangents(other.tangents),
	bitangents(other.bitangents),
	colors(other.colors),
	uvs(other.uvs),
	indices(other.indices)
{}


SubMeshVertexData::SubMeshVertexData(SubMeshVertexData && other) :
	positions(std::move(other.positions)),
	normals(std::move(other.normals)),
	tangents(std::move(other.tangents)),
	bitangents(std::move(other.bitangents)),
	colors(std::move(other.colors)),
	uvs(std::move(other.uvs)),
	indices(std::move(other.indices))
{}


SubMeshVertexData & SubMeshVertexData::operator=(const SubMeshVertexData & other)
{
	this->positions		= other.positions;
	this->normals		= other.normals;
	this->tangents		= other.tangents;
	this->bitangents	= other.bitangents;
	this->colors		= other.colors;
	this->uvs			= other.uvs;
	this->indices		= other.indices;

	return *this;
}


SubMeshVertexData & SubMeshVertexData::operator=(SubMeshVertexData && other)
{
	this->positions		= std::move(other.positions);
	this->normals		= std::move(other.normals);
	this->tangents		= std::move(other.tangents);
	this->bitangents	= std::move(other.bitangents);
	this->colors		= std::move(other.colors);
	this->uvs			= std::move(other.uvs);
	this->indices		= std::move(other.indices);

	return *this;
}


//SubMesh::SubMesh(SubMesh && other) :
//	name(std::move(other.name)),
//	vertexData(std::move(other.vertexData)),
//	material(other.material),
//	VBOs(std::move(other.VBOs)),
//	VAO(other.VAO)
//	{
//		other.VAO = 0;
//		other.material = nullptr;
//	}


SubMesh::SubMesh(const SubMeshVertexData& vertexData, Material* material) :
	vertexData(vertexData),
	material(material)
{
	markOutdated();
}


SubMesh::SubMesh(SubMeshVertexData&& vertexData, Material* material) : 
	vertexData(std::move(vertexData)),
	material(material)
{
	markOutdated();
}



SubMesh::~SubMesh()
{
	freeGpuMemory();
}


void SubMesh::setMaterial(Material * material)
{
	getResourceLock().lock();
	this->material = material;
	getResourceLock().unlock();
}


void SubMesh::freeGpuMemory_Internal()
{
	// Delete previously allocated buffers
	glDeleteBuffers((GLsizei)VBOs.size(), VBOs.data());
	glDeleteVertexArrays(1, &VAO);

	getGLInternalPixelFormat<glm::vec3>();

}





template<class VectorType>
GLuint createVertexBufferObject(const std::vector<VectorType>& vertexData, const std::optional<std::tuple<GLuint, GLuint>> vao_and_attributeIndex = {})
{
	auto type			= getGLDataType<decltype(VectorType().x)>();
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


void SubMesh::updateGpuMemory_Internal()
{
	freeGpuMemory_Internal();

	if (glGetError() != GL_NO_ERROR)
	{
		std::cout << "error" << std::endl;
	}

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


GLuint SubMesh::getVertexArrayObject() const
{
	return VAO;
}


const SubMeshVertexData & SubMesh::getVertexData() const
{
	return this->vertexData;
}


Material * SubMesh::getMaterial()
{
	return material;
}


bool Mesh::load()
{
	
	static_assert(sizeof(glm::vec3) == sizeof(aiVector3D));
	static_assert(sizeof(glm::vec4) == sizeof(aiColor4D));
	
	Assimp::Importer importer;
	
	if (auto pScene = importer.ReadFile(getAssetPath().c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace))
	{
		this->subMeshes.clear();
		//this->subMeshes = std::set<SubMesh>(pScene->mNumMeshes);
		
		uint64_t alloc = 0;
		uint64_t populate = 0;
		
		for (auto i = 0u; i < pScene->mNumMeshes; i++)
		{
			
			auto aiMesh			= pScene->mMeshes[i];
			stopwatch::Stopwatch sw;
			sw.start();
			SubMeshVertexData vertexData;
			vertexData.positions.resize(aiMesh->mNumVertices);
			vertexData.normals.resize(aiMesh->mNumVertices);
			vertexData.tangents.resize(aiMesh->mNumVertices);
			vertexData.bitangents.resize(aiMesh->mNumVertices);
			vertexData.colors.resize(aiMesh->mNumVertices);
			vertexData.uvs.resize(aiMesh->GetNumUVChannels());
			for (auto& uvs : vertexData.uvs)
			{
				uvs.resize(aiMesh->mNumVertices);
			}
			vertexData.indices.resize(aiMesh->mNumFaces * 3u);

			alloc += sw.elapsed();
			sw.start();
			
			if (aiMesh->HasPositions())
			{
				std::memcpy(vertexData.positions.data(), aiMesh->mVertices, aiMesh->mNumVertices * sizeof(glm::vec3));
			}
			if (aiMesh->HasNormals())
			{
				std::memcpy(vertexData.normals.data(), aiMesh->mNormals, aiMesh->mNumVertices * sizeof(glm::vec3));
			}
			if (aiMesh->HasTangentsAndBitangents())
			{
				std::memcpy(vertexData.tangents.data(), aiMesh->mTangents, aiMesh->mNumVertices * sizeof(glm::vec3));
				std::memcpy(vertexData.bitangents.data(), aiMesh->mBitangents, aiMesh->mNumVertices * sizeof(glm::vec3));
			}
			if (aiMesh->HasVertexColors(0))
			{
				std::memcpy(vertexData.colors.data(), aiMesh->mColors[0], aiMesh->mNumVertices * sizeof(aiColor4D));
			}
			for (auto c = 0u; c < aiMesh->GetNumUVChannels(); c++)
			{
				std::memcpy(vertexData.uvs[c].data(), aiMesh->mTextureCoords[c], aiMesh->mNumVertices * sizeof(glm::vec3));
			}

			for (auto fi = 0u; fi < aiMesh->mNumFaces; fi++)
			{
				auto& face = aiMesh->mFaces[fi];
				assert(face.mNumIndices == 3);
				vertexData.indices[fi * 3 ]		= (face.mIndices[0]);
				vertexData.indices[fi * 3 + 1]	= (face.mIndices[1]);
				vertexData.indices[fi * 3 + 2]	= (face.mIndices[2]);
				//std::memcpy(&vertexData.indices[fi], face.mIndices, 3 * sizeof(unsigned int));
			}

			addSubMesh(std::move(vertexData), nullptr);
			
			populate += sw.elapsed();
		}

		//std::cout << "populate took " << populate << "ms. " << std::endl;
		return true;	
	}	
	else
	{
		std::cerr << "Failed to load mesh from '" << getAssetPath() << "'. Assimp error: " << importer.GetErrorString() << std::endl;;
	}

	return false;
}


bool Mesh::reload()
{
	return true;
}


SubMesh* Mesh::addSubMesh(const SubMeshVertexData& vertexData, Material * material)
{
	return this->subMeshes.emplace_back(new SubMesh(std::move(vertexData), material)).get();
}


SubMesh* Mesh::addSubMesh(SubMeshVertexData&& vertexData, Material * material)
{
	return this->subMeshes.emplace_back(new SubMesh(std::move(vertexData), material)).get();
}