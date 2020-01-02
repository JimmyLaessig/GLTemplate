#pragma once
#include <gl/glew.h>
//#include "Math.h"
#include "glm/glm.hpp"
#include "Material.h"
#include <vector>
#include "GpuResource.h"
#include "SharedAsset.h"

struct SubMeshVertexData
{

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    std::vector<glm::vec4> colors;
	std::vector<std::vector<glm::vec3>> uvs;

    std::vector<unsigned int> indices;
};

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec4 color;
    std::vector<glm::vec3> uvs;
};


class SubMesh : public GpuResource
{
public:
	friend class Mesh;

    SubMesh() = default;


    virtual ~SubMesh();

    /**
     * @brief Set the Vertex Data object
     * 
     * @param vertexData 
     */
    void setVertexData(const SubMeshVertexData& vertexData);
    
    /**
     * @brief Set the Vertex Data object
     * 
     * @param vertexData 
     */
    void setVertexData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    /**
     * @brief Set the Material object
     * 
     * @param material 
     */
    void setMaterial(Material* material);	

    /**
     * @brief Get the Vertex Data object
     * 
     * @return const SubMeshVertexData& 
     */
    const SubMeshVertexData& getVertexData();

    /**
     * @brief Get the Material object
     * 
     * @return Material* 
     */
    Material* getMaterial();

protected:

	/**
	 * @brief
	 *
	 */
	virtual void freeGpuMemory_Internal() override;

	/**
	 * @brief
	 *
	 */
	virtual void updateGpuMemory_Internal() override;
	

private: 		

	std::string name = "";

	SubMeshVertexData vertexData;
      
    Material* material;
	
	std::vector<GLuint> VBOs;
	GLuint VAO = 0;

};


class Mesh : public SharedAsset
{
public: 
    Mesh() = default;

    std::vector<SubMesh> subMeshes;

	virtual bool load() override;

	virtual bool reload() override;
};
