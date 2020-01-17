#include "Rendering/Mesh.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>
#include <optional>
#include "GL/glew.h"


IndexedGeometryData::IndexedGeometryData(const IndexedGeometryData & other) :
	positions(other.positions),
	normals(other.normals),
	tangents(other.tangents),
	bitangents(other.bitangents),
	colors(other.colors),
	uvs(other.uvs),
	indices(other.indices)
{}


IndexedGeometryData::IndexedGeometryData(IndexedGeometryData && other) :
	positions(std::move(other.positions)),
	normals(std::move(other.normals)),
	tangents(std::move(other.tangents)),
	bitangents(std::move(other.bitangents)),
	colors(std::move(other.colors)),
	uvs(std::move(other.uvs)),
	indices(std::move(other.indices))
{}


IndexedGeometryData & IndexedGeometryData::operator=(const IndexedGeometryData & other)
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


IndexedGeometryData & IndexedGeometryData::operator=(IndexedGeometryData && other)
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


IndexedGeometry::IndexedGeometry(const IndexedGeometryData& vertexData, Material* material) :
	vertexData(vertexData),
	material(material)
{
	markOutdated();
}


IndexedGeometry::IndexedGeometry(IndexedGeometryData&& vertexData, Material* material) :
	vertexData(std::move(vertexData)),
	material(material)
{
	markOutdated();
}



IndexedGeometry::~IndexedGeometry()
{
	freeGpuMemory();
}


void IndexedGeometry::setMaterial(Material * material)
{
	getResourceLock().lock();
	this->material = material;
	getResourceLock().unlock();
}









const IndexedGeometryData & IndexedGeometry::getVertexData() const
{
	return this->vertexData;
}


Material * IndexedGeometry::getMaterial()
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
			IndexedGeometryData vertexData;
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


IndexedGeometry* Mesh::addSubMesh(const IndexedGeometryData& vertexData, Material * material)
{
	// TODO // return this->subMeshes.emplace_back(new GLIndexedGeometry(std::move(vertexData), material)).get();
	return nullptr;
}


IndexedGeometry* Mesh::addSubMesh(IndexedGeometryData&& vertexData, Material * material)
{
	//return this->subMeshes.emplace_back(new IndexedGeometry(std::move(vertexData), material)).get();
	return nullptr;
}