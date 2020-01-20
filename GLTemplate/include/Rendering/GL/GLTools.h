#pragma once

//#include "Math.h"

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "VectorMath.h"
#include "Rendering/Texture.h"


template<typename T>
inline GLenum getGLDataType() 
{ 
	return getGLDataType<decltype(T().x)>();
};

template<> inline GLenum getGLDataType<int8_t>()		{ return GL_BYTE; }
template<> inline GLenum getGLDataType<uint8_t>()	{ return GL_UNSIGNED_BYTE; }
template<> inline GLenum getGLDataType<int16_t>()	{ return GL_SHORT; }
template<> inline GLenum getGLDataType<uint16_t>()	{ return GL_UNSIGNED_SHORT; }
template<> inline GLenum getGLDataType<int32_t>()	{ return GL_INT; }
template<> inline GLenum getGLDataType<uint32_t>()	{ return GL_UNSIGNED_INT; }
template<> inline GLenum getGLDataType<float>()		{ return GL_FLOAT; }
template<> inline GLenum getGLDataType<double>()		{ return GL_DOUBLE; }





template<class PixelType> 
inline GLenum getGLPixelFormat()
{
	switch (PixelType::length())
	{
	case 1:
		return GL_R;
	case 2:
		return GL_RG;
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	default:
		assert(false);
		return GL_R;
	}
}


template<> inline GLenum getGLPixelFormat<float>()	{ return GL_R; }
template<> inline GLenum getGLPixelFormat<short>()	{ return GL_R; }
template<> inline GLenum getGLPixelFormat<uint8_t>()	{ return GL_R; }
template<> inline GLenum getGLPixelFormat<uint16_t>(){ return GL_R; }
template<> inline GLenum getGLPixelFormat<uint32_t>(){ return GL_R; }



template<int Channels, class PixelType> inline GLenum getGLInternalPixelFormat() { PixelType::no_implementation; }

// ------------------------------------------------
// Float32
// ------------------------------------------------
template<> inline GLenum getGLInternalPixelFormat<1, float>() { return GL_R32F; }
template<> inline GLenum getGLInternalPixelFormat<2, float>() { return GL_RG32F; }
template<> inline GLenum getGLInternalPixelFormat<3, float>() { return GL_RGB32F; }
template<> inline GLenum getGLInternalPixelFormat<4, float>() { return GL_RGBA32F; }


// ------------------------------------------------
// int32
// ------------------------------------------------
template<> inline GLenum getGLInternalPixelFormat<1, int32_t>(){ return GL_R32I; }
template<> inline GLenum getGLInternalPixelFormat<2, int32_t>(){ return GL_RG32I; }
template<> inline GLenum getGLInternalPixelFormat<3, int32_t>(){ return GL_RGB32I; }
template<> inline GLenum getGLInternalPixelFormat<4, int32_t>(){ return GL_RGBA32I; }

// ------------------------------------------------
// uint32
// ------------------------------------------------
template<> inline GLenum getGLInternalPixelFormat<1, uint32_t>(){ return GL_R32I; }
template<> inline GLenum getGLInternalPixelFormat<2, uint32_t>(){ return GL_RG32I; }
template<> inline GLenum getGLInternalPixelFormat<3, uint32_t>(){ return GL_RGB32I; }
template<> inline GLenum getGLInternalPixelFormat<4, uint32_t>(){ return GL_RGBA32I; }

// ------------------------------------------------
// int16
// ------------------------------------------------
template<> inline GLenum getGLInternalPixelFormat<1, int16_t>(){ return GL_R16I; }
template<> inline GLenum getGLInternalPixelFormat<2, int16_t>(){ return GL_RG16I; }
template<> inline GLenum getGLInternalPixelFormat<3, int16_t>(){ return GL_RGB16I; }
template<> inline GLenum getGLInternalPixelFormat<4, int16_t>(){ return GL_RGBA16I; }

// ------------------------------------------------
// uint16
// ------------------------------------------------
template<> inline GLenum getGLInternalPixelFormat<1, uint16_t>() { return GL_R16UI; }
template<> inline GLenum getGLInternalPixelFormat<2, uint16_t>() { return GL_RG16UI; }
template<> inline GLenum getGLInternalPixelFormat<3, uint16_t>() { return GL_RGB16UI; }
template<> inline GLenum getGLInternalPixelFormat<4, uint16_t>(){ return GL_RGBA16UI; }

// ------------------------------------------------
// int8 / byte
// ------------------------------------------------
template<> inline GLenum getGLInternalPixelFormat<1, int8_t>() { return GL_R8; }
template<> inline GLenum getGLInternalPixelFormat<2, int8_t>() { return GL_RG8; }
template<> inline GLenum getGLInternalPixelFormat<3, int8_t>() { return GL_RGB8; }
template<> inline GLenum getGLInternalPixelFormat<4, int8_t>() { return GL_RGBA8; }

// ------------------------------------------------
// uint8 / unsigned byte
// ------------------------------------------------
template<> inline GLenum getGLInternalPixelFormat<1, uint8_t>() { return GL_RG; }
template<> inline GLenum getGLInternalPixelFormat<2, uint8_t>() { return GL_RG8; }
template<> inline GLenum getGLInternalPixelFormat<3, uint8_t>() { return GL_RGB8; }
template<> inline GLenum getGLInternalPixelFormat<4, uint8_t>() { return GL_RGBA8; }



//template<class T>
//inline GLenum getGLInternalPixelFormat() { getGLInternalPixelFormat<1, T>(); }

//template<glm::vec<2, class T, class Q> inline GLenum getGLInternalPixelFormat() { getGLInternalPixelFormat<2, T>(); }
//template<glm::vec<3, class T, class Q> inline GLenum getGLInternalPixelFormat() { getGLInternalPixelFormat<3, T>(); }
//template<glm::vec<4, class T, class Q> inline GLenum getGLInternalPixelFormat() { getGLInternalPixelFormat<4, T>(); }

//template<typename T, glm::qualifier Q>
//inline GLenum getGLInternalPixelFormat(glm::vec<1, T, Q> v) { getGLInternalPixelFormat<1, T>(); }


GLenum inline getGLDataType(const PixelInfo& info)
{
	switch (info.DataType)
	{
	//case PixelDataType::DOUBLE:			return getGLDataType<double>();
	case PixelDataType::FLOAT:			return getGLDataType<float>();
	case PixelDataType::BYTE:			return getGLDataType<int8_t>();
	case PixelDataType::UNSIGNED_BYTE:	return getGLDataType<uint8_t>();
	case PixelDataType::SHORT:			return getGLDataType<int16_t>();
	case PixelDataType::UNSIGNED_SHORT: return getGLDataType<uint16_t>();
	case PixelDataType::UNSIGNED_INT:	return getGLDataType<int32_t>();
	case PixelDataType::INT:			return getGLDataType<uint32_t>();
	default:
		return GL_BYTE;
	}
}


GLenum inline getGLPixelFormat(const PixelInfo& info)
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




template<int Channel>
GLenum inline getGLInternalPixelFormat(PixelDataType info)
{
	switch (info)
	{
		case PixelDataType::BYTE			: return getGLInternalPixelFormat<Channel, int8_t>();
		case PixelDataType::UNSIGNED_BYTE	: return getGLInternalPixelFormat<Channel, uint8_t>();
		case PixelDataType::SHORT			: return getGLInternalPixelFormat<Channel, int16_t>();
		case PixelDataType::UNSIGNED_SHORT	: return getGLInternalPixelFormat<Channel, uint16_t>();
		case PixelDataType::INT				: return getGLInternalPixelFormat<Channel, int32_t>();
		case PixelDataType::UNSIGNED_INT	: return getGLInternalPixelFormat<Channel, uint32_t>();
		case PixelDataType::FLOAT			: return getGLInternalPixelFormat<Channel, float>();
		//case PixelDataType::DOUBLE			: return getGLInternalPixelFormat<1, double>();
		default								: return getGLInternalPixelFormat<Channel, uint8_t>();
	}
}


GLenum inline getGLInternalPixelFormat(const PixelInfo& info)
{
	switch (info.Channels)
	{
		case PixelChannels::R	: return getGLInternalPixelFormat<1>(info.DataType);
		case PixelChannels::RG	: return getGLInternalPixelFormat<2>(info.DataType);
		case PixelChannels::RGB	: return getGLInternalPixelFormat<3>(info.DataType);
		case PixelChannels::RGBA: return getGLInternalPixelFormat<4>(info.DataType);
		default					: return getGLInternalPixelFormat<1>(info.DataType);
	}

	return GL_FALSE;
}