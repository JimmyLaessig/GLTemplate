#pragma once

//#include "Math.h"
#include <vector>
#include <memory>
#include "Material.h"
#include "glm/glm.hpp"
#include "Components/IndexedGeometry.h"
#include "SharedAsset.h"



class Mesh : public SharedAsset
{
public: 
	friend class SharedAsset;
	

	/**
	 *
	 */
	IndexedGeometry* addSubMesh(const IndexedGeometryData& vertexData, Material* material);

	/**
	 *
	 */
	IndexedGeometry* addSubMesh(IndexedGeometryData&& vertexData, Material* material);

	/**
	 *
	 */
	std::vector<std::unique_ptr<IndexedGeometry>> subMeshes;

private: 

	Mesh() = default;
};



class MeshLoader
{
public: 
	static bool Load(Mesh* mesh, const std::string_view path);
};