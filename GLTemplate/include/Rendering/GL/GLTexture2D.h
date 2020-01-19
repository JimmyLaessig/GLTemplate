#pragma once


#include "Rendering/GpuResource.h"
#include "VectorMath.h"
#include "Rendering/GL/GLTools.h"

/**
 *
 */
template<class PixelType>
class GLTexture2D : public GpuResource
{
public: 
	
	/**
	 *
	 */
	virtual void updateGpuMemory_Internal() override
	{
		freeGpuMemory_Internal();

		bool err = glGetError() == GL_NO_ERROR;

		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);

		auto internalFormat = getGLInternalPixelFormat<PixelType>();
		auto format			= getGLPixelFormat<PixelType>();
		auto type			= getGLDataType<PixelType>();
		
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, format, type, textureData.data());
		glGenerateMipmap(GL_TEXTURE_2D);
		

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		err = glGetError() == GL_NO_ERROR;
		
	}

	/**
	 *
	 */
	virtual void freeGpuMemory_Internal() override
	{
		glDeleteTextures(1, &handle);
	}

	/**
	 *
	 */
	GLuint handle = 0;	
};