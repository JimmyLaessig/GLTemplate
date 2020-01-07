#include "Mesh.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>

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
	this->positions = other.positions;
	this->normals = other.normals;
	this->tangents = other.tangents;
	this->bitangents = other.bitangents;
	this->colors = other.colors;
	this->uvs = other.uvs;
	this->indices = other.indices;

	return *this;
}


SubMeshVertexData & SubMeshVertexData::operator=(SubMeshVertexData && other)
{
	this->positions = std::move(other.positions);
	this->normals = std::move(other.normals);
	this->tangents = std::move(other.tangents);
	this->bitangents = std::move(other.bitangents);
	this->colors = std::move(other.colors);
	this->uvs = std::move(other.uvs);
	this->indices = std::move(other.indices);

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
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &vertexData.positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	
	// Fill Normal Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &vertexData.normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Tangent Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &vertexData.tangents[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Bitangent Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3),&vertexData.bitangents[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill Color Buffer
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec4), &vertexData.colors[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	// Fill UV Buffer(s)
	for (auto& uvs : vertexData.uvs)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(bufferIndex);
		glVertexAttribPointer(bufferIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
		bufferIndex++;
	}
	
	// Fill Index Buffer
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[bufferIndex]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexData.indices.size() * sizeof(unsigned int), &vertexData.indices[0], GL_STATIC_DRAW);
	}
	

	glBindVertexArray(0);
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
			vertexData.indices.resize(aiMesh->mNumFaces * 3u);
			
			
			for (auto& uvs : vertexData.uvs)
			{
				uvs.resize(aiMesh->mNumVertices);
			}

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
				std::memcpy(&vertexData.indices[fi], face.mIndices, 3);
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




//RenderObject toRenderObject(const SubMesh* subMesh)
//{
//	return RenderObject{
//		nullptr,
//		nullptr,
//		[vbo = subMesh->getVertexArrayObject(), count = subMesh->getVertexData().indices.size()]()
//		{
//			glBindVertexArray(vbo);
//			glDrawElements(
//				GL_TRIANGLES,		// mode
//				count,				// count
//				GL_UNSIGNED_INT,	// type
//				(void*)0			// element array buffer offset
//			);
//			}
//	};
//}