#pragma once

//#include "Math.h"

#include "GL/glew.h"



template<typename T>
GLenum toGLDataType() { T::unimplemented_function; };


template<> GLenum toGLDataType<int8_t>() { return GL_BYTE; }
template<> GLenum toGLDataType<uint8_t>() { return GL_UNSIGNED_BYTE; }
template<> GLenum toGLDataType<int16_t>() { return GL_SHORT; }
template<> GLenum toGLDataType<uint16_t>() { return GL_UNSIGNED_SHORT; }
template<> GLenum toGLDataType<int32_t>() { return GL_INT; }
template<> GLenum toGLDataType<uint32_t>() { return GL_UNSIGNED_INT; }
template<> GLenum toGLDataType<float>() { return GL_FLOAT; }
template<> GLenum toGLDataType<double>() { return GL_DOUBLE; }