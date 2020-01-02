#include "Mesh.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>
  
SubMesh::~SubMesh()
{
	freeGpuMemory();
}


void SubMesh::setVertexData(const SubMeshVertexData & vertexData)
{
	getResourceLock().lock();
	this->vertexData.positions	= vertexData.positions;
	this->vertexData.normals	= vertexData.normals;
	this->vertexData.tangents	= vertexData.tangents;
	this->vertexData.bitangents = vertexData.bitangents;
	this->vertexData.uvs		= vertexData.uvs;
	this->vertexData.indices	= vertexData.indices;

	for (auto& v : this->vertexData.normals)	{v = glm::normalize(v);};
	for (auto& v : this->vertexData.tangents)	{v = glm::normalize(v);};
	for (auto& v : this->vertexData.bitangents)	{v = glm::normalize(v);};
	
	auto numVertices = this->vertexData.positions.size();

	assert(this->vertexData.normals.size() == numVertices);
	assert(this->vertexData.tangents.size() == numVertices);
	assert(this->vertexData.bitangents.size() == numVertices);
	for (auto& uvSet : this->vertexData.uvs){assert(uvSet.size() == numVertices);}

	getResourceLock().unlock();

	markOutdated();
}


void SubMesh::setVertexData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{	
	getResourceLock().lock();

	auto numVertices = vertices.size();

	// Determine the max
	size_t numUVChannels = numVertices <= 0 ? 0 : vertices[0].uvs.size();
		
	this->vertexData = SubMeshVertexData();
	
	this->vertexData.positions.reserve(numVertices);
	this->vertexData.normals.reserve(numVertices);
	this->vertexData.tangents.reserve(numVertices);
	this->vertexData.bitangents.reserve(numVertices);
	this->vertexData.colors.reserve(numVertices);

	this->vertexData.uvs.reserve(numUVChannels);
	for (auto& uvSet : vertexData.uvs){uvSet.reserve(numVertices);}

	for (auto& v : vertices)
	{
		vertexData.positions.push_back(v.position);
		vertexData.normals.push_back(glm::normalize(v.normal));
		vertexData.tangents.push_back(glm::normalize(v.tangent));
		vertexData.bitangents.push_back(glm::normalize(v.bitangent));
		vertexData.colors.push_back(v.color);
		
		assert(vertexData.uvs.size() == numUVChannels);

		int i = 0;
		for (auto& uv : v.uvs)
		{
			vertexData.uvs[i++].push_back(uv);
		}	
	}

	this->vertexData.indices = indices;
	
	getResourceLock().unlock();

	markOutdated();
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
}


void SubMesh::updateGpuMemory_Internal()
{
	freeGpuMemory_Internal();

	auto numVertices = vertexData.positions.size();
	auto bufferIndex = 0u;

	// Generate OpenGL Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		
	// Positions	= 0
	// Normals		= 1
	// Tangents		= 2
	// Bitangents	= 3
	// Colors		= 4
	// UVs			= 5..
	// Indices		= Last
	// Generate OpenGL Buffers
	VBOs.resize(6 + vertexData.uvs.size(), 0u);
	glGenBuffers((GLsizei)VBOs.size(), VBOs.data());

		
	// Fill Position Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), vertexData.positions.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Normal Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), vertexData.normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Tangent Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), vertexData.tangents.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Bitangent Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), vertexData.bitangents.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Color Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec4), vertexData.colors.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill UV Buffer(s)
	for (auto& uvs : vertexData.uvs)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Index Buffer
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexData.indices.size() * sizeof(unsigned int), vertexData.indices.data(), GL_STATIC_DRAW);
	}	
}


const SubMeshVertexData & SubMesh::getVertexData()
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
		this->subMeshes = std::vector<SubMesh>(pScene->mNumMeshes);
		
		uint64_t alloc = 0;
		uint64_t populate = 0;
		
		for (auto i = 0u; i < pScene->mNumMeshes; i++)
		{
			SubMesh& subMesh	= subMeshes[i];
			auto aiMesh			= pScene->mMeshes[i];
			stopwatch::Stopwatch sw;
			sw.start();
			subMesh.vertexData.positions.resize(aiMesh->mNumVertices);
			subMesh.vertexData.normals.resize(aiMesh->mNumVertices);
			subMesh.vertexData.tangents.resize(aiMesh->mNumVertices);
			subMesh.vertexData.bitangents.resize(aiMesh->mNumVertices);
			subMesh.vertexData.colors.resize(aiMesh->mNumVertices);
			subMesh.vertexData.uvs.resize(aiMesh->GetNumUVChannels());
			subMesh.vertexData.indices.resize(aiMesh->mNumFaces * 3);
			subMesh.name = aiMesh->mName.C_Str();
			
			for (auto& uvs : subMesh.vertexData.uvs)
			{
				uvs.resize(aiMesh->mNumVertices);
			}

			alloc += sw.elapsed();
			sw.start();
			
			if (aiMesh->HasPositions())
			{
				std::memcpy(subMesh.vertexData.positions.data(), aiMesh->mVertices, aiMesh->mNumVertices * sizeof(glm::vec3));
			}
			if (aiMesh->HasNormals())
			{
				std::memcpy(subMesh.vertexData.normals.data(), aiMesh->mNormals, aiMesh->mNumVertices * sizeof(glm::vec3));
			}
			if (aiMesh->HasTangentsAndBitangents())
			{
				std::memcpy(subMesh.vertexData.tangents.data(), aiMesh->mTangents, aiMesh->mNumVertices * sizeof(glm::vec3));
				std::memcpy(subMesh.vertexData.bitangents.data(), aiMesh->mBitangents, aiMesh->mNumVertices * sizeof(glm::vec3));
			}
			if (aiMesh->HasVertexColors(0))
			{
				std::memcpy(subMesh.vertexData.colors.data(), aiMesh->mColors[0], aiMesh->mNumVertices * sizeof(aiColor4D));
			}
			for (auto c = 0u; c < aiMesh->GetNumUVChannels(); c++)
			{
				std::memcpy(subMesh.vertexData.uvs[c].data(), aiMesh->mTextureCoords[c], aiMesh->mNumVertices * sizeof(glm::vec3));
			}

			for (auto fi = 0u; fi < aiMesh->mNumFaces; fi++)
			{
				auto& face = aiMesh->mFaces[fi];
				assert(face.mNumIndices == 3);
				std::memcpy(&subMesh.vertexData.indices[fi], face.mIndices, 3);
			}

			subMesh.markOutdated();

			populate += sw.elapsed();
		}

		std::cout << "populate took " << populate << "ms. " << std::endl;
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