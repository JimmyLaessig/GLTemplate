#pragma once

#include "Rendering/internal/BaseObject.h"
#include "Rendering/Types/TextureFormat.h"


#include <string>
#include <optional>
#include <span>
#include <memory>

namespace Rendering
{

class GLTEMPLATE_API ITexture : public Rendering::BaseObject
{
public:
	using Rendering::BaseObject::BaseObject;

	using Ptr = std::shared_ptr<ITexture>;


	virtual void* getNativeHandle() = 0;


	virtual TextureFormat getTextureFormat() const = 0;



};


class GLTEMPLATE_API ITexture2D : public ITexture
{
public:

	using Rendering::ITexture::ITexture;

	struct Config
	{
		Rendering::TextureFormat format;

		size_t width{ 0 };
		size_t height{ 0 };

		std::span<std::byte> data;

		bool generateMipmaps{ false };
	};

	using Ptr = std::shared_ptr<ITexture2D>;


	virtual size_t getHeight() const = 0;


	virtual size_t getWidth() const = 0;


	virtual bool hasMipmaps() const = 0;

};


//class GLTEMPLATE_API ITextureCube : public ITexture
//{
//public:
//
//	virtual void* getNativeHandle() = 0;
//
//};
}
