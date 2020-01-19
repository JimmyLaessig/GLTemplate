#pragma once

#include "GpuResource.h"
#include "VectorMath.h"


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

	virtual void resize(glm::u32vec2 size);


protected:

	std::vector<PixelType> textureData = {};

	glm::u32vec2 size = { 0,0 };

};