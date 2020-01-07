#pragma once

//#include "Math.h"
#include <vector>
#include <memory>
#include "Material.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GpuResource.h"
#include "SharedAsset.h"


struct SubMeshVertexData
{
	SubMeshVertexData() = default;

	SubMeshVertexData(const SubMeshVertexData& other);

	SubMeshVertexData(SubMeshVertexData&& other);

	SubMeshVertexData& operator=(const SubMeshVertexData& other);

	SubMeshVertexData& operator=(SubMeshVertexData&& other);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    std::vector<glm::vec4> colors;
	std::vector<std::vector<glm::vec3>> uvs;

    std::vector<unsigned int> indices;
};



class SubMesh : public DrawableGpuResource
{
public:
	friend class Mesh;


	SubMesh();

	/**
	 *
	 */
	SubMesh(const SubMeshVertexData& vertexData, Material * material);

	/**
	 *
	 */
	SubMesh(SubMeshVertexData&& vertexData, Material * material);


	//SubMesh(SubMesh&& other) noexcept;


    virtual ~SubMesh();


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
    const SubMeshVertexData& getVertexData() const;

    /**
     * @brief Get the Material object
     * 
     * @return Material* 
     */
    Material* getMaterial();


	GLuint getVertexArrayObject() const;

	
	std::function<void()> getDrawCall() const override
	{
		return [vbo = getVertexArrayObject(), count = (GLsizei)getVertexData().indices.size()]()
		{
			glBindVertexArray(vbo);
			glDrawElements(
				GL_TRIANGLES,		// mode
				count,				// count
				GL_UNSIGNED_INT,	// type
				(void*)0			// element array buffer offset
			);
		};
	}

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
	
	GLuint VAO;

	std::vector<GLuint> VBOs;

public: 
	

};


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
	SubMesh* addSubMesh(const SubMeshVertexData& vertexData, Material* material);

	/**
	 *
	 */
	SubMesh* addSubMesh(SubMeshVertexData&& vertexData, Material* material);


	std::vector<std::unique_ptr<SubMesh>> subMeshes;
};
