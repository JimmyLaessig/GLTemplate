#pragma once

//#include "Math.h"
#include <vector>
#include <memory>
#include "Material.h"
#include "glm/glm.hpp"
#include "IndexedGeometry.h"
#include "SharedAsset.h"



class Mesh : public SharedAsset
{
public: 
    Mesh() = default;


	/**
	 *
	 */
	virtual bool load() override;

	/**
	 *
	 */
	virtual bool reload() override;

	/**
	 *
	 */
	IndexedGeometry* addSubMesh(const IndexedGeometryData& vertexData, Material* material);

	/**
	 *
	 */
	IndexedGeometry* addSubMesh(IndexedGeometryData&& vertexData, Material* material);


	std::vector<std::unique_ptr<IndexedGeometry>> subMeshes;
};