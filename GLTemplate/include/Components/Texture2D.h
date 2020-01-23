#pragma once

#include "Components/Texture.h"
#include "VectorMath.h"
#include "Rendering/GpuTexture.h"

//enum class TextureFormat
//{
//	RED,
//	RG,
//	RGB,
//	RGBA,
//	DEPTH,
//	DEPTH_STENCIL
//}


template<class PixelType>
class Texture2D : public ITexture
{
	
public:

	Texture2D(const glm::u32vec2& size, const std::vector<PixelType>& textureData) : 
		ITexture(),	
		backendTexture(GpuResourceBackend::get()->createBackendTexture2D(this))
	{
		setTextureData(size, textureData);	
	}

	Texture2D(const glm::u32vec2& size, PixelType defaultValue) : 
		ITexture(),
		backendTexture(GpuResourceBackend::get()->createBackendTexture2D(this))
	{
		setTextureData(size, defaultValue);
	}


	void setTextureData(glm::u32vec2 size, const std::vector<PixelType>& textureData)
	{
		assert(size.x * size.y == textureData.size());
		this->textureData = textureData;
		this->size = size;
		this->backendTexture->markOutdated();
	}


	void setTextureData(glm::u32vec2 size, PixelType defaultValue)
	{
		this->textureData.resize(size.x * size.y, defaultValue);
		this->size = size;
		this->backendTexture->markOutdated();
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


	virtual const IBackendTexture* getBackendTexture() const override
	{
		if(backendTexture)
			return backendTexture.get();

		return nullptr;
	}

	const std::vector<PixelType>& getData() const
	{
		return textureData;
	}


protected:

	std::vector<PixelType> textureData;


	glm::u32vec2 size = { 0,0 };


	std::unique_ptr<IBackendTexture> backendTexture;
};





