#pragma once


#include "GpuResource.h"
#include "VectorMath.h"
#include "GL.h"



template<class PixelType>
class Texture2D : public GpuResource
{
public: 


	Texture2D(glm::u32vec2 size, const std::vector<PixelType>& textureData) : GpuResource()
	{
		setTextureData(size, textureData);
	}

	Texture2D(glm::u32vec2 size, PixelType defaultValue) : GpuResource()
	{
		setTextureData(size, defaultValue);
	}


	void setTextureData(glm::u32vec2 size, const std::vector<PixelType>& textureData)
	{
		assert(size.x * size.y == textureData.size());
		this->textureData = textureData;
		this->size = size;
		this->markOutdated();
	}


	void setTextureData(glm::u32vec2 size, PixelType defaultValue)
	{
		this->textureData.resize(size.x * size.y, defaultValue);
		this->size = size;
		this->markOutdated();
	}


	// Inherited via GpuResource
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


	virtual void freeGpuMemory_Internal() override
	{
		glDeleteTextures(1, &handle);
	}

	GLuint handle = 0;

private: 

	std::vector<PixelType> textureData = {};

	glm::u32vec2 size = {0,0};

	
};


