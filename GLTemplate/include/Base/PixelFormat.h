#pragma once
#include "Base/System.h"
#include <stdint.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <cstddef>

namespace Base
{
namespace PixelFormat
{
	using Red8		= uint8_t;
	using Red16		= uint16_t;
	using Red32		= uint32_t;
	using Red32F	= float;

	using RG8		= glm::vec<2, uint8_t>;
	using RG16		= glm::vec<2, uint16_t>;
	using RG32		= glm::vec<2, uint32_t>;
	using RG32F		= glm::vec<2, float>;
	
	using RGB8		= glm::vec<3, uint8_t>;
	using RGB16		= glm::vec<3, uint16_t>;
	using RGB32		= glm::vec<3, uint32_t>;
	using RGB32F	= glm::vec<3, float>;

	using RGBA8		= glm::vec<4, uint8_t>;
	using RGBA16	= glm::vec<4, uint16_t>;
	using RGBA32	= glm::vec<4, uint32_t>;
	using RGBA32F	= glm::vec<4, float>;

	struct Depth16 
	{
		uint8_t data[2];
	};

	struct Depth24
	{ 
		uint8_t data[3];
	};

	struct Depth32
	{
		float data;
	};

	struct Depth24Stencil8
	{ 
		uint8_t data[4];
	};


	template<typename T>
	T* value_ptr(T& p)
	{
		return &p;
	}


	template<typename T>
	const T* value_ptr(const T& p) { return &p; }


	template<typename T, size_t DIM>
	T* value_ptr(glm::vec<DIM, T>& p) { return glm::value_ptr(p); }


	template<typename T, size_t DIM>
	const T* value_ptr(const glm::vec<DIM, T>& p) { return glm::value_ptr(p); }

	

	inline uint8_t* value_ptr(Base::PixelFormat::Depth16& p) { return p.data; }
	inline const uint8_t* value_ptr(const Base::PixelFormat::Depth16& p) { return p.data; }

	inline uint8_t* value_ptr(Base::PixelFormat::Depth24& p){return p.data;}
	inline const uint8_t* value_ptr(const Base::PixelFormat::Depth24& p){return p.data;}

	inline float* value_ptr(Base::PixelFormat::Depth32& p){return &p.data;}
	inline const float* value_ptr(const Base::PixelFormat::Depth32& p){return &p.data;}

	inline uint8_t* value_ptr(Base::PixelFormat::Depth24Stencil8& p) { return p.data; }
	inline const uint8_t* value_ptr(const Base::PixelFormat::Depth24Stencil8& p) { return p.data; }

}
}
