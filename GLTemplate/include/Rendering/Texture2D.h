#pragma once

#include "Rendering/Texture.h"
#include "VectorMath.h"
#include "Rendering/BackendTexture.h"



template<class PixelType>
class Texture2D : public ITexture
{
public:

	Texture2D(const glm::u32vec2& size, const std::vector<PixelType>& textureData) 
		: ITexture()	
	{
		setTextureData(size, textureData);
		this->backendTexture = GpuResourceBackend::get()->createBackendTexture2D(this);
	}

	Texture2D(const glm::u32vec2& size, PixelType defaultValue) 
		: ITexture()
	{
		setTextureData(size, defaultValue);
		this->backendTexture = GpuResourceBackend::get()->createBackendTexture2D(this);
	}


	void setTextureData(glm::u32vec2 size, const std::vector<PixelType>& textureData)
	{
		assert(size.x * size.y == textureData.size());
		this->textureData = textureData;
		this->size = size;
		//this->markOutdated();
	}


	void setTextureData(glm::u32vec2 size, PixelType defaultValue)
	{
		this->textureData.resize(size.x * size.y, defaultValue);
		this->size = size;
		//this->markOutdated();
	}


	virtual glm::u32vec2 getTextureSize() const override
	{
		return size;
	}


	virtual size_t getTextureSizeInBytes() const override
	{
		return size.x * size.x * sizeof(PixelType);
	}


	virtual const void* getTextureDataPtr() const override
	{
		return (void*)textureData.data();
	}


	virtual PixelInfo getPixelInfo() const override
	{
		return PixelInfo(
			toPixelChannels<PixelType>(),
			toPixelDataType<PixelType>()
		);
	}

protected:

	std::vector<PixelType> textureData;


	glm::u32vec2 size = { 0,0 };


	std::unique_ptr<IBackendTexture> backendTexture;
};