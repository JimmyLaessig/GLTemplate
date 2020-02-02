#pragma once

#include "Material.h"
#include "Rendering/GpuIndexedGeometry.h"
#include <vector>
#include "VectorMath.h"

struct IndexedGeometryData
{
	IndexedGeometryData() = default;

	IndexedGeometryData(const IndexedGeometryData& other) = default;

	IndexedGeometryData(IndexedGeometryData&& other) = default;

	IndexedGeometryData& operator=(const IndexedGeometryData& other) = default;

	IndexedGeometryData& operator=(IndexedGeometryData&& other) = default;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	std::vector<glm::vec4> colors;
	std::vector<std::vector<glm::vec3>> uvs;

	std::vector<unsigned int> indices;
};



class IndexedGeometry
{
public:
	friend class Mesh;


	IndexedGeometry() = delete;

	/**
	 *
	 */
	IndexedGeometry(const IndexedGeometryData& vertexData, Material * material, const std::string_view name = "");

	/**
	 *
	 */
	IndexedGeometry(IndexedGeometryData&& vertexData, Material * material, const std::string_view name = "");


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

	std::string name;

	IndexedGeometryData vertexData;

	Material* material;

private: 

	std::unique_ptr<IBackendIndexedGeometry> backendIndexedGeometry;
};
