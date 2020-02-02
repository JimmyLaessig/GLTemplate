#pragma once
#include "Rendering/GL/GL.h"
#include "Rendering/GpuIndexedGeometry.h"

class IndexedGeometry;

/**
 *
 */
class GLIndexedGeometry : public IBackendIndexedGeometry
{
public:


	GLIndexedGeometry(const IndexedGeometry* geometry);


	virtual ~GLIndexedGeometry();


	/**
	 *
	 */
	GLuint getVertexArrayObject() const;


	///**
	// *
	// */
	//std::function<void()> getDrawCall() const
	//{
	//	return [vao = getVertexArrayObject(), count = (GLsizei)getVertexData().indices.size()]()
	//	{
	//		glBindVertexArray(vao);
	//		if (glGetError() != GL_NO_ERROR)
	//		{
	//			std::cout << "error" << std::endl;
	//		}
	//		glDrawElements(
	//			GL_TRIANGLES,		// mode
	//			count,				// count
	//			GL_UNSIGNED_INT,	// type
	//			(void*)0			// element array buffer offset
	//		);
	//	};
	//}


protected:

	/**
	 * @brief
	 *
	 */
	virtual void freeGpuMemoryImpl() override;

	/**
	 * @brief
	 *
	 */
	virtual void updateGpuMemoryImpl() override;


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