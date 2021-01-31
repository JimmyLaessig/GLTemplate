#pragma once
#include "Rendering/Types/DataType.h"

#include <variant>

namespace Rendering
{

ENUM_CLASS(DepthFormat,
	DEPTH16,
	DEPTH24,
	DEPTH32,
	DEPTH24STENCIL8
);


ENUM_CLASS(ColorFormat, 
	R8I,
	RG8I,
	RGB8I,
	RGBA8I,

	R8UI,
	RG8UI,
	RGB8UI,
	RGBA8UI,

	R16I,
	RG16I,
	RGB16I,
	RGBA16I,

	R16UI,
	RG16UI,
	RGB16UI,
	RGBA16UI,

	R32I,
	RG32I,
	RGB32I,
	RGBA32I,

	R32UI,
	RG32UI,
	RGB32UI,
	RGBA32UI,

	R16F,
	RG16F,
	RGB16F,
	RGBA16F,

	R32F,
	RG32F,
	RGB32F,
	RGBA32F,
);


struct TextureFormat : public std::variant<ColorFormat, DepthFormat>
{};


constexpr DataType
getDataType(ColorFormat format)
{
	switch (format)
	{
		case ColorFormat::R8I:		return DataType::INT8;
		case ColorFormat::RG8I:		return DataType::INT8;
		case ColorFormat::RGB8I:	return DataType::INT8;
		case ColorFormat::RGBA8I: 	return DataType::INT8;
										
		case ColorFormat::R8UI:		return DataType::UINT8;
		case ColorFormat::RG8UI:	return DataType::UINT8;
		case ColorFormat::RGB8UI:	return DataType::UINT8;
		case ColorFormat::RGBA8UI: 	return DataType::UINT8;
										  
		case ColorFormat::R16I:		return DataType::INT16;
		case ColorFormat::RG16I:	return DataType::INT16;
		case ColorFormat::RGB16I:	return DataType::INT16;
		case ColorFormat::RGBA16I: 	return DataType::INT16;
										
		case ColorFormat::R16UI:	return DataType::UINT16;
		case ColorFormat::RG16UI:	return DataType::UINT16;
		case ColorFormat::RGB16UI:	return DataType::UINT16;
		case ColorFormat::RGBA16UI: return DataType::UINT16;
		
		case ColorFormat::R32I:		return DataType::INT32;
		case ColorFormat::RG32I:	return DataType::INT32;
		case ColorFormat::RGB32I:	return DataType::INT32;
		case ColorFormat::RGBA32I: 	return DataType::INT32;

		case ColorFormat::R32UI:	return DataType::UINT32;
		case ColorFormat::RG32UI:	return DataType::UINT32;
		case ColorFormat::RGB32UI:	return DataType::UINT32;
		case ColorFormat::RGBA32UI: return DataType::UINT32;
							 
		case ColorFormat::R16F:		return DataType::FLOAT16;
		case ColorFormat::RG16F:	return DataType::FLOAT16;
		case ColorFormat::RGB16F:	return DataType::FLOAT16;
		case ColorFormat::RGBA16F: 	return DataType::FLOAT16;
										  
		case ColorFormat::R32F:		return DataType::FLOAT32;
		case ColorFormat::RG32F:	return DataType::FLOAT32;
		case ColorFormat::RGB32F:	return DataType::FLOAT32;
		case ColorFormat::RGBA32F: 	return DataType::FLOAT32;
	}

	assert(false);
	return {};
}


constexpr DataType
getDataType(DepthFormat format)
{
	switch (format)
	{
		case Rendering::DepthFormat::DEPTH16:			return DataType::UINT16;
		case Rendering::DepthFormat::DEPTH24:			return DataType::UINT8;
		case Rendering::DepthFormat::DEPTH24STENCIL8:	return DataType::UINT8;
		case Rendering::DepthFormat::DEPTH32:			return DataType::FLOAT32;
	}
	assert(false);
	return {};
}


constexpr DataType
getDataType(TextureFormat format)
{
	return std::visit([](auto f) 
	{
		return getDataType(f); 
	}, format);
}


constexpr size_t 
length(ColorFormat channels)
{
	switch (channels)
	{
		case ColorFormat::R8I:		return 1;
		case ColorFormat::RG8I:		return 2;
		case ColorFormat::RGB8I:	return 3;
		case ColorFormat::RGBA8I: 	return 4;
			
		case ColorFormat::R8UI:		return 1;
		case ColorFormat::RG8UI:	return 2;
		case ColorFormat::RGB8UI:	return 3;
		case ColorFormat::RGBA8UI: 	return 4;
				
		case ColorFormat::R16I:		return 1;
		case ColorFormat::RG16I:	return 2;
		case ColorFormat::RGB16I:	return 3;
		case ColorFormat::RGBA16I: 	return 4;
				
		case ColorFormat::R16UI:	return 1;
		case ColorFormat::RG16UI:	return 2;
		case ColorFormat::RGB16UI:	return 3;
		case ColorFormat::RGBA16UI: return 4;
				
		case ColorFormat::R32UI:	return 1;
		case ColorFormat::RG32UI:	return 2;
		case ColorFormat::RGB32UI:	return 3;
		case ColorFormat::RGBA32UI: return 4;
				
		case ColorFormat::R32I:		return 1;
		case ColorFormat::RG32I:	return 2;
		case ColorFormat::RGB32I:	return 3;
		case ColorFormat::RGBA32I: 	return 4;
				
		case ColorFormat::R16F:		return 1;
		case ColorFormat::RG16F:	return 2;
		case ColorFormat::RGB16F:	return 3;
		case ColorFormat::RGBA16F: 	return 4;
				
		case ColorFormat::R32F:		return 1;
		case ColorFormat::RG32F:	return 2;
		case ColorFormat::RGB32F:	return 3;
		case ColorFormat::RGBA32F: 	return 4;

	};
	assert(false);
	return 0;
}


constexpr size_t
sizeInBytes(DepthFormat type)
{
	switch (type)
	{
	case DepthFormat::DEPTH16:			return 2;
	case DepthFormat::DEPTH24:			return 3;
	case DepthFormat::DEPTH24STENCIL8:	return 4;
	case DepthFormat::DEPTH32:			return 4;
	};
	assert(false);
	return 0;
}


constexpr size_t 
sizeInBytes(const ColorFormat& format)
{
	return sizeInBytes(getDataType(format)) * length(format);
}


constexpr size_t 
sizeInBytes(const TextureFormat& format)
{
	return std::visit([](auto v) { return sizeInBytes(v); }, format);
}
}