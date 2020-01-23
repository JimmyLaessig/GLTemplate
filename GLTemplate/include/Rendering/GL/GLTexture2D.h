#pragma once

#include "Rendering/GL/GLTypeConversion.h"
#include "Rendering/GpuTexture.h"


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
	virtual void updateGpuMemoryImpl() override
	{
		freeGpuMemoryImpl();

		bool err = glGetError() == GL_NO_ERROR;

		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);

		auto size			= texture->getTextureSize();
		auto pixelInfo		= texture->getPixelInfo();
		auto internalFormat = GLTypeConversion::toGLInternalPixelFormat(pixelInfo);
		auto format			= GLTypeConversion::toGLPixelFormat(pixelInfo);
		auto type			= GLTypeConversion::toGLDataType(pixelInfo);
		

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, format, type, texture->getTextureDataPtr());
		glGenerateMipmap(GL_TEXTURE_2D);
		

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		err = glGetError() == GL_NO_ERROR;	
	}


	/**
	 *
	 */
	virtual void freeGpuMemoryImpl() override
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