#pragma once

#include "GpuResource.h"
#include "Material.h"


struct IndexedGeometryData
{
	IndexedGeometryData() = default;

	IndexedGeometryData(const IndexedGeometryData& other);

	IndexedGeometryData(IndexedGeometryData&& other);

	IndexedGeometryData& operator=(const IndexedGeometryData& other);

	IndexedGeometryData& operator=(IndexedGeometryData&& other);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	std::vector<glm::vec4> colors;
	std::vector<std::vector<glm::vec3>> uvs;

	std::vector<unsigned int> indices;
};



class IndexedGeometry : public DrawableGpuResource
{
public:
	friend class Mesh;


	IndexedGeometry() = delete;

	/**
	 *
	 */
	IndexedGeometry(const IndexedGeometryData& vertexData, Material * material);

	/**
	 *
	 */
	IndexedGeometry(IndexedGeometryData&& vertexData, Material * material);


	//SubMesh(SubMesh&& other) noexcept;


	virtual ~IndexedGeometry();


	/**
	 * @brief Set the Material object
	 *
	 * @param material
	 */
	void setMaterial(Material* material);

	/**
	 * @brief Get the Vertex Data object
	 *
	 * @return const IndexedGeometryData&
	 */
	const IndexedGeometryData& getVertexData() const;

	/**
	 * @brief Get the Material object
	 *
	 * @return Material*
	 */
	Material* getMaterial();


protected:

	std::string name = "";

	IndexedGeometryData vertexData = {};

	Material* material = nullptr;
};