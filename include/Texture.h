#pragma once


#include "GpuResource.h"
#include "VectorMath.h"
#include "GL.h"


//
//template<class PixelType>
//class Texture2D : public GpuResource
//{
//public: 
//
//	Texture2D(glm::u32vec2 size, const std::vector<PixelType>& textureData)
//	{
//		
//	}
//
//	virtual void resize(glm::u32vec2 size);
//
//
//
//private: 
//
//	std::vector<PixelType> textureData;
//
//	glm::u32vec2 size;
//
//	GLuint handle;
//	// Inherited via GpuResource
//	virtual void updateGpuMemory_Internal() override
//	{
//		freeGpuMemory_Internal();
//		glGenTextures(1, &handle);
//		glBindTexture(handle);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBBA_ )
//		
//	}
//
//	virtual void freeGpuMemory_Internal() override
//	{
//		glDeleteTextures(1, handle);
//	}
//
//};
//
//
//
//
//
