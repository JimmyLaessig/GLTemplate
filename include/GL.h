#pragma once

//#include "Math.h"

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "VectorMath.h"



template<typename T>
constexpr GLenum getGLDataType() 
{ 
	return getGLDataType<decltype(T().x)>();
};

template<> constexpr GLenum getGLDataType<int8_t>()		{ return GL_BYTE; }
template<> constexpr GLenum getGLDataType<uint8_t>()	{ return GL_UNSIGNED_BYTE; }
template<> constexpr GLenum getGLDataType<int16_t>()	{ return GL_SHORT; }
template<> constexpr GLenum getGLDataType<uint16_t>()	{ return GL_UNSIGNED_SHORT; }
template<> constexpr GLenum getGLDataType<int32_t>()	{ return GL_INT; }
template<> constexpr GLenum getGLDataType<uint32_t>()	{ return GL_UNSIGNED_INT; }
template<> constexpr GLenum getGLDataType<float>()		{ return GL_FLOAT; }
template<> constexpr GLenum getGLDataType<double>()		{ return GL_DOUBLE; }




template<class PixelType> 
constexpr GLenum getGLPixelFormat()
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

template<> constexpr GLenum getGLPixelFormat<float>()	{ return GL_R; }
template<> constexpr GLenum getGLPixelFormat<short>()	{ return GL_R; }
template<> constexpr GLenum getGLPixelFormat<uint8_t>()	{ return GL_R; }
template<> constexpr GLenum getGLPixelFormat<uint16_t>(){ return GL_R; }
template<> constexpr GLenum getGLPixelFormat<uint32_t>(){ return GL_R; }


template<class PixelType> inline GLenum getGLInternalPixelFormat() { PixelType::no_implementation; }


// ------------------------------------------------
// Float32
// ------------------------------------------------
template<> constexpr GLenum getGLInternalPixelFormat<float>()		{ return GL_R32F; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::vec1>()	{ return GL_R32F; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::vec2>()	{ return GL_RG32F; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::vec3>()	{ return GL_RGB32F; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::vec4>()	{ return GL_RGBA32F; }


// ------------------------------------------------
// int32
// ------------------------------------------------
template<> constexpr GLenum getGLInternalPixelFormat<int>()			{ return GL_R32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::ivec1>()	{ return GL_R32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::ivec2>()	{ return GL_RG32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::ivec3>()	{ return GL_RGB32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::ivec4>()	{ return GL_RGBA32I; }

// ------------------------------------------------
// uint32
// ------------------------------------------------
template<> constexpr GLenum getGLInternalPixelFormat<uint32_t>()	{ return GL_R32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u32vec1>(){ return GL_R32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u32vec2>(){ return GL_RG32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u32vec3>(){ return GL_RGB32I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u32vec4>(){ return GL_RGBA32I; }

// ------------------------------------------------
// int16
// ------------------------------------------------
template<> constexpr GLenum getGLInternalPixelFormat<int16_t>()		{ return GL_R16I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i16vec1>(){ return GL_R16I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i16vec2>(){ return GL_RG16I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i16vec3>(){ return GL_RGB16I; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i16vec4>(){ return GL_RGBA16I; }

// ------------------------------------------------
// uint16
// ------------------------------------------------
template<> constexpr GLenum getGLInternalPixelFormat<uint16_t>()	{ return GL_R16UI; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u16vec1>(){ return GL_R16UI; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u16vec2>(){ return GL_RG16UI; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u16vec3>(){ return GL_RGB16UI; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u16vec4>(){ return GL_RGBA16UI; }

// ------------------------------------------------
// int8 / byte
// ------------------------------------------------
template<> constexpr GLenum getGLInternalPixelFormat<int8_t>()		{ return GL_R8; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i8vec1>() { return GL_R8; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i8vec2>() { return GL_RG8; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i8vec3>() { return GL_RGB8; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::i8vec4>() { return GL_RGBA8; }

// ------------------------------------------------
// uint8 / unsigned byte
// ------------------------------------------------
template<> constexpr GLenum getGLInternalPixelFormat<uint8_t>()		{ return GL_R8; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u8vec1>() { return GL_RG; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u8vec2>() { return GL_RG8; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u8vec3>() { return GL_RGB8; }
template<> constexpr GLenum getGLInternalPixelFormat<glm::u8vec4>() { return GL_RGBA8; }