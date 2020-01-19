#pragma once

#include "Rendering/Mesh.h"
#include "Rendering/GL/GLTools.h"


/**
 *
 */
class GLIndexedGeometry : public IndexedGeometry
{
public:
	/**
	 *
	 */
	virtual ~GLIndexedGeometry();

	/**
	 *
	 */
	GLuint getVertexArrayObject() const;

	/**
	 *
	 */
	std::function<void()> getDrawCall() const
	{
		return [vao = getVertexArrayObject(), count = (GLsizei)getVertexData().indices.size()]()
		{
			glBindVertexArray(vao);
			if (glGetError() != GL_NO_ERROR)
			{
				std::cout << "error" << std::endl;
			}
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
	/**
	 *
	 */
	GLuint VAO = 0u;
	/**
	 *
	 */
	std::vector<GLuint> VBOs;
};