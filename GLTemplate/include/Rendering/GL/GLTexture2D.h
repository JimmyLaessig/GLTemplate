#pragma once

#include "Rendering/GL/GLTools.h"
#include "Rendering/BackendTexture.h"


class GLTexture2D : public IBackendTexture
{
public: 

	GLTexture2D(const ITexture* texture)
		:IBackendTexture(texture)
	{
		markOutdated();
	}

	virtual ~GLTexture2D()
	{
		freeGpuMemory();
	}

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
		auto size			= texture->getTextureSize();
		auto pixelInfo		= texture->getPixelInfo();
		auto internalFormat = getGLInternalPixelFormat(pixelInfo);
		auto format			= getGLPixelFormat(pixelInfo);
		auto type			= getGLDataType(pixelInfo);
		
		assert(format == GL_RGBA);
		assert(internalFormat == GL_RGBA8);
		assert(type == GL_UNSIGNED_BYTE);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, format, type, texture->getTextureDataPtr());
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
	unsigned int handle = 0;	


private:

	GLenum internalFormat;
	GLenum format;
	GLenum type;
};