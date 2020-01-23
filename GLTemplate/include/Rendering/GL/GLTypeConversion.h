#pragma once

//#include "Math.h"

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "VectorMath.h"
#include "Components/Texture.h"

namespace GLTypeConversion
{

	/**
	 * Gets the correct GL enum for the templated type T
	 */
	template<typename T>
	inline GLenum toGLDataType()
	{
		return toGLDataType<decltype(T().x)>();
	};

	template<> inline GLenum toGLDataType<int8_t>()		{ return GL_BYTE; }
	template<> inline GLenum toGLDataType<uint8_t>()	{ return GL_UNSIGNED_BYTE; }
	template<> inline GLenum toGLDataType<int16_t>()	{ return GL_SHORT; }
	template<> inline GLenum toGLDataType<uint16_t>()	{ return GL_UNSIGNED_SHORT; }
	template<> inline GLenum toGLDataType<int32_t>()	{ return GL_INT; }
	template<> inline GLenum toGLDataType<uint32_t>()	{ return GL_UNSIGNED_INT; }
	template<> inline GLenum toGLDataType<float>()		{ return GL_FLOAT; }
	template<> inline GLenum toGLDataType<double>()		{ return GL_DOUBLE; }


	/**
	 * Gets the correct GL enum for the given PixelInfo
	 */
	GLenum inline toGLDataType(const PixelInfo& info)
	{
		switch (info.DataType)
		{
		case PixelDataType::FLOAT:			return toGLDataType<float>();
		case PixelDataType::BYTE:			return toGLDataType<int8_t>();
		case PixelDataType::UNSIGNED_BYTE:	return toGLDataType<uint8_t>();
		case PixelDataType::SHORT:			return toGLDataType<int16_t>();
		case PixelDataType::UNSIGNED_SHORT: return toGLDataType<uint16_t>();
		case PixelDataType::UNSIGNED_INT:	return toGLDataType<int32_t>();
		case PixelDataType::INT:			return toGLDataType<uint32_t>();
		default:
			return GL_BYTE;
		}
	}


	/**
	 * Gets the pixel format enum for the templated PixelType
	 */
	template<class PixelType>
	inline GLenum toGLPixelFormat()
	{
		switch (PixelType::length())
		{
		case 1:
			return GL_RED;
		case 2:
			return GL_RG;
		case 3:
			return GL_RGB;
		case 4:
			return GL_RGBA;
		default:
			assert(false);
			return GL_RED;
		}
	}


	template<> inline GLenum toGLPixelFormat<float>() { return GL_RED; }
	template<> inline GLenum toGLPixelFormat<short>() { return GL_RED; }
	template<> inline GLenum toGLPixelFormat<uint8_t>() { return GL_RED; }
	template<> inline GLenum toGLPixelFormat<uint16_t>() { return GL_RED; }
	template<> inline GLenum toGLPixelFormat<uint32_t>() { return GL_RED; }


	/**
	 * Returns the pixel format enum for the given PixelInfo.
	 */
	GLenum inline toGLPixelFormat(const PixelInfo& info)
	{
		switch (info.Channels)
		{
		case PixelChannels::R:		return GL_R;
		case PixelChannels::RG:		return GL_RG;
		case PixelChannels::RGB:	return GL_RGB;
		case PixelChannels::RGBA:	return GL_RGBA;
		default:					return GL_R;
		}
	}


	/**
	 * Gets the internal pixel format enum for the given channel and PixelType
	 */
	template<int Channels, class PixelType> inline GLenum toGLInternalPixelFormat() { PixelType::no_implementation; }


	// ------------------------------------------------
	// Float32
	// ------------------------------------------------
	template<> inline GLenum toGLInternalPixelFormat<1, float>() { return GL_R32F; }
	template<> inline GLenum toGLInternalPixelFormat<2, float>() { return GL_RG32F; }
	template<> inline GLenum toGLInternalPixelFormat<3, float>() { return GL_RGB32F; }
	template<> inline GLenum toGLInternalPixelFormat<4, float>() { return GL_RGBA32F; }


	// ------------------------------------------------
	// int32
	// ------------------------------------------------
	template<> inline GLenum toGLInternalPixelFormat<1, int32_t>() { return GL_R32I; }
	template<> inline GLenum toGLInternalPixelFormat<2, int32_t>() { return GL_RG32I; }
	template<> inline GLenum toGLInternalPixelFormat<3, int32_t>() { return GL_RGB32I; }
	template<> inline GLenum toGLInternalPixelFormat<4, int32_t>() { return GL_RGBA32I; }

	// ------------------------------------------------
	// uint32
	// ------------------------------------------------
	template<> inline GLenum toGLInternalPixelFormat<1, uint32_t>() { return GL_R32UI; }
	template<> inline GLenum toGLInternalPixelFormat<2, uint32_t>() { return GL_RG32UI; }
	template<> inline GLenum toGLInternalPixelFormat<3, uint32_t>() { return GL_RGB32UI; }
	template<> inline GLenum toGLInternalPixelFormat<4, uint32_t>() { return GL_RGBA32UI; }

	// ------------------------------------------------
	// int16
	// ------------------------------------------------
	template<> inline GLenum toGLInternalPixelFormat<1, int16_t>() { return GL_R16I; }
	template<> inline GLenum toGLInternalPixelFormat<2, int16_t>() { return GL_RG16I; }
	template<> inline GLenum toGLInternalPixelFormat<3, int16_t>() { return GL_RGB16I; }
	template<> inline GLenum toGLInternalPixelFormat<4, int16_t>() { return GL_RGBA16I; }

	// ------------------------------------------------
	// uint16
	// ------------------------------------------------
	template<> inline GLenum toGLInternalPixelFormat<1, uint16_t>() { return GL_R16UI; }
	template<> inline GLenum toGLInternalPixelFormat<2, uint16_t>() { return GL_RG16UI; }
	template<> inline GLenum toGLInternalPixelFormat<3, uint16_t>() { return GL_RGB16UI; }
	template<> inline GLenum toGLInternalPixelFormat<4, uint16_t>() { return GL_RGBA16UI; }

	// ------------------------------------------------
	// int8 / byte
	// ------------------------------------------------
	template<> inline GLenum toGLInternalPixelFormat<1, int8_t>() { return GL_R8; }
	template<> inline GLenum toGLInternalPixelFormat<2, int8_t>() { return GL_RG8; }
	template<> inline GLenum toGLInternalPixelFormat<3, int8_t>() { return GL_RGB8; }
	template<> inline GLenum toGLInternalPixelFormat<4, int8_t>() { return GL_RGBA8; }

	// ------------------------------------------------
	// uint8 / unsigned byte
	// ------------------------------------------------
	template<> inline GLenum toGLInternalPixelFormat<1, uint8_t>() { return GL_R8; }
	template<> inline GLenum toGLInternalPixelFormat<2, uint8_t>() { return GL_RG8; }
	template<> inline GLenum toGLInternalPixelFormat<3, uint8_t>() { return GL_RGB8; }
	template<> inline GLenum toGLInternalPixelFormat<4, uint8_t>() { return GL_RGBA8; }


	/**
	 * Gets the internal format enum for the given PixelDataType and Channel.
	 */
	template<int Channel>
	GLenum inline toGLInternalPixelFormat(PixelDataType info)
	{
		// Maximum 4 channels are allowed
		static_assert(Channel > 0 && Channel <= 4);

		switch (info)
		{
			case PixelDataType::BYTE:			return toGLInternalPixelFormat<Channel, int8_t>();
			case PixelDataType::UNSIGNED_BYTE:	return toGLInternalPixelFormat<Channel, uint8_t>();
			case PixelDataType::SHORT:			return toGLInternalPixelFormat<Channel, int16_t>();
			case PixelDataType::UNSIGNED_SHORT: return toGLInternalPixelFormat<Channel, uint16_t>();
			case PixelDataType::INT:			return toGLInternalPixelFormat<Channel, int32_t>();
			case PixelDataType::UNSIGNED_INT:	return toGLInternalPixelFormat<Channel, uint32_t>();
			case PixelDataType::FLOAT:			return toGLInternalPixelFormat<Channel, float>();
				//case PixelDataType::DOUBLE			: return toGLInternalPixelFormat<1, double>();
			default: return toGLInternalPixelFormat<Channel, uint8_t>();
		}
	}


	/**
	 * Returns the internal format enum for the given PixelInfo
	 */
	GLenum inline toGLInternalPixelFormat(const PixelInfo& info)
	{
		switch (info.Channels)
		{
			case PixelChannels::R: return toGLInternalPixelFormat<1>(info.DataType);
			case PixelChannels::RG: return toGLInternalPixelFormat<2>(info.DataType);
			case PixelChannels::RGB: return toGLInternalPixelFormat<3>(info.DataType);
			case PixelChannels::RGBA: return toGLInternalPixelFormat<4>(info.DataType);
			default: return toGLInternalPixelFormat<1>(info.DataType);
		}

		return GL_FALSE;
	}
}