#include "Components/Mesh.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>
#include <optional>
#include "Rendering/GpuResourceBackend.h"
#include "Rendering/GL/GLResourceBackend.h"


IndexedGeometry* Mesh::addSubMesh(const IndexedGeometryData& vertexData, Material * material)
{
	return this->subMeshes.emplace_back(std::make_unique<IndexedGeometry>(vertexData, material)).get(); 
}


IndexedGeometry* Mesh::addSubMesh(IndexedGeometryData&& vertexData, Material * material)
{
	return this->subMeshes.emplace_back(std::make_unique<IndexedGeometry>(vertexData, material)).get();
}


bool MeshLoader::Load(Mesh* mesh, const std::string_view path)
{
	static_assert(sizeof(glm::vec3) == sizeof(aiVector3D));
	static_assert(sizeof(glm::vec4) == sizeof(aiColor4D));

	Assimp::Importer importer;

	if (auto pScene = importer.ReadFile(path.data(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace))
	{
		mesh->subMeshes.clear();

		for (auto i = 0u; i < pScene->mNumMeshes; i++)
		{
			auto aiMesh = pScene->mMeshes[i];
			
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
				vertexData.indices[fi * 3] = (face.mIndices[0]);
				vertexData.indices[fi * 3 + 1] = (face.mIndices[1]);
				vertexData.indices[fi * 3 + 2] = (face.mIndices[2]);
			}
			mesh->addSubMesh(std::move(vertexData), nullptr);
		}

		return true;
	}
	else
	{
		std::cerr << "Failed to load mesh from '" << path.data() << "'. Assimp error: " << importer.GetErrorString() << std::endl;;
	}

	return false;
}
