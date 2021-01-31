#pragma once
#include "Rendering/Types/DataType.h"
#include "glm/glm.hpp"

namespace Rendering
{
ENUM_CLASS(AttributeFormat,
	FLOAT,
	FLOAT_VEC2,
	FLOAT_VEC3,
	FLOAT_VEC4,

	INT,
	INT_VEC2,
	INT_VEC3,
	INT_VEC4,

	UNSIGNED_INT,
	UNSIGNED_INT_VEC2,
	UNSIGNED_INT_VEC3,

	UNSIGNED_INT_VEC4,
	DOUBLE,
	DOUBLE_VEC2,
	DOUBLE_VEC3,
	DOUBLE_VEC4,

	FLOAT_MATRIX22,
	FLOAT_MATRIX33,
	FLOAT_MATRIX44,
	FLOAT_MATRIX23,
	FLOAT_MATRIX24,
	FLOAT_MATRIX32,
	FLOAT_MATRIX34,
	FLOAT_MATRIX42,
	FLOAT_MATRIX43,

	DOUBLE_MATRIX22,
	DOUBLE_MATRIX33,
	DOUBLE_MATRIX44,
	DOUBLE_MATRIX23,
	DOUBLE_MATRIX24,
	DOUBLE_MATRIX32,
	DOUBLE_MATRIX34,
	DOUBLE_MATRIX42,
	DOUBLE_MATRIX43
);


constexpr size_t 
length(AttributeFormat format)
{
	 switch (format)
	{
		case AttributeFormat::FLOAT:				return 1;
		case AttributeFormat::FLOAT_VEC2:			return 2;
		case AttributeFormat::FLOAT_VEC3:			return 3;
		case AttributeFormat::FLOAT_VEC4:			return 4;

		case AttributeFormat::INT:					return 1;
		case AttributeFormat::INT_VEC2:				return 2;
		case AttributeFormat::INT_VEC3:				return 3;
		case AttributeFormat::INT_VEC4:				return 4;

		case AttributeFormat::UNSIGNED_INT:			return 1;
		case AttributeFormat::UNSIGNED_INT_VEC2:	return 2;
		case AttributeFormat::UNSIGNED_INT_VEC3:	return 3;
		case AttributeFormat::UNSIGNED_INT_VEC4:	return 4;

		case AttributeFormat::DOUBLE:				return 1;
		case AttributeFormat::DOUBLE_VEC2:			return 2;
		case AttributeFormat::DOUBLE_VEC3:			return 3;
		case AttributeFormat::DOUBLE_VEC4:			return 4;

		case AttributeFormat::FLOAT_MATRIX22:		return 4;
		case AttributeFormat::FLOAT_MATRIX33:		return 9;
		case AttributeFormat::FLOAT_MATRIX44:		return 16;
		case AttributeFormat::FLOAT_MATRIX23:		return 8;
		case AttributeFormat::FLOAT_MATRIX24:		return 8;
		case AttributeFormat::FLOAT_MATRIX32:		return 6;
		case AttributeFormat::FLOAT_MATRIX34:		return 12;
		case AttributeFormat::FLOAT_MATRIX42:		return 8;
		case AttributeFormat::FLOAT_MATRIX43:		return 12;

		case AttributeFormat::DOUBLE_MATRIX22:		return 4;
		case AttributeFormat::DOUBLE_MATRIX33:		return 9;
		case AttributeFormat::DOUBLE_MATRIX44:		return 16;
		case AttributeFormat::DOUBLE_MATRIX23:		return 6;
		case AttributeFormat::DOUBLE_MATRIX24:		return 8;
		case AttributeFormat::DOUBLE_MATRIX32:		return 6;
		case AttributeFormat::DOUBLE_MATRIX34:		return 12;
		case AttributeFormat::DOUBLE_MATRIX42:		return 8;
		case AttributeFormat::DOUBLE_MATRIX43:		return 12;
	}

	assert(false);
	return 0;
}


constexpr DataType
getDataType(AttributeFormat format)
{
	switch (format)
	{
		case AttributeFormat::FLOAT:				return DataType::FLOAT32;
		case AttributeFormat::FLOAT_VEC2:			return DataType::FLOAT32;
		case AttributeFormat::FLOAT_VEC3:			return DataType::FLOAT32;
		case AttributeFormat::FLOAT_VEC4:			return DataType::FLOAT32;
														 
		case AttributeFormat::INT:					return DataType::INT32;
		case AttributeFormat::INT_VEC2:				return DataType::INT32;
		case AttributeFormat::INT_VEC3:				return DataType::INT32;
		case AttributeFormat::INT_VEC4:				return DataType::INT32;
														 
		case AttributeFormat::UNSIGNED_INT:			return DataType::UINT32;
		case AttributeFormat::UNSIGNED_INT_VEC2:	return DataType::UINT32;
		case AttributeFormat::UNSIGNED_INT_VEC3:	return DataType::UINT32;
		case AttributeFormat::UNSIGNED_INT_VEC4:	return DataType::UINT32;
														 
		case AttributeFormat::DOUBLE:				return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_VEC2:			return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_VEC3:			return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_VEC4:			return DataType::DOUBLE;
														  
		case AttributeFormat::FLOAT_MATRIX22:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX33:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX44:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX23:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX24:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX32:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX34:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX42:		return DataType::FLOAT32;
		case AttributeFormat::FLOAT_MATRIX43:		return DataType::FLOAT32;
														  
		case AttributeFormat::DOUBLE_MATRIX22:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX33:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX44:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX23:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX24:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX32:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX34:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX42:		return DataType::DOUBLE;
		case AttributeFormat::DOUBLE_MATRIX43:		return DataType::DOUBLE;
	}

	assert(false);
	return DataType::FLOAT32;
}


constexpr size_t
sizeInBytes(AttributeFormat format)
{
	return sizeInBytes(getDataType(format)) * length(format);
}


template<typename T> constexpr AttributeFormat toAttributeFormat()
{
	T::no_implementation;
}

template<> constexpr AttributeFormat toAttributeFormat<float>()		{ return AttributeFormat::FLOAT;		}
template<> constexpr AttributeFormat toAttributeFormat<glm::vec2>() { return AttributeFormat::FLOAT_VEC2;	}
template<> constexpr AttributeFormat toAttributeFormat<glm::vec3>() { return AttributeFormat::FLOAT_VEC3;	}
template<> constexpr AttributeFormat toAttributeFormat<glm::vec4>() { return AttributeFormat::FLOAT_VEC4;	}

template<> constexpr AttributeFormat toAttributeFormat<int32_t>()	{ return AttributeFormat::INT;		}
template<> constexpr AttributeFormat toAttributeFormat<glm::ivec2>(){ return AttributeFormat::INT_VEC2;	}
template<> constexpr AttributeFormat toAttributeFormat<glm::ivec3>(){ return AttributeFormat::INT_VEC3;	}
template<> constexpr AttributeFormat toAttributeFormat<glm::ivec4>(){ return AttributeFormat::INT_VEC4;	}

template<> constexpr AttributeFormat toAttributeFormat<uint32_t>()	{ return AttributeFormat::UNSIGNED_INT;		}
template<> constexpr AttributeFormat toAttributeFormat<glm::uvec2>(){ return AttributeFormat::UNSIGNED_INT_VEC2;}
template<> constexpr AttributeFormat toAttributeFormat<glm::uvec3>(){ return AttributeFormat::UNSIGNED_INT_VEC3;}
template<> constexpr AttributeFormat toAttributeFormat<glm::uvec4>(){ return AttributeFormat::UNSIGNED_INT_VEC4;}

template<> constexpr AttributeFormat toAttributeFormat<double>()	{ return AttributeFormat::DOUBLE;		}
template<> constexpr AttributeFormat toAttributeFormat<glm::dvec2>(){ return AttributeFormat::DOUBLE_VEC2;	}
template<> constexpr AttributeFormat toAttributeFormat<glm::dvec3>(){ return AttributeFormat::DOUBLE_VEC3;	}
template<> constexpr AttributeFormat toAttributeFormat<glm::dvec4>(){ return AttributeFormat::DOUBLE_VEC4;	}

template<> constexpr AttributeFormat toAttributeFormat<glm::mat2>()	 { return AttributeFormat::FLOAT_MATRIX22;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat3>()	 { return AttributeFormat::FLOAT_MATRIX33;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat4>()	 { return AttributeFormat::FLOAT_MATRIX44;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat2x3>(){ return AttributeFormat::FLOAT_MATRIX23;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat2x4>(){ return AttributeFormat::FLOAT_MATRIX24;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat3x2>(){ return AttributeFormat::FLOAT_MATRIX32;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat3x4>(){ return AttributeFormat::FLOAT_MATRIX34;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat4x2>(){ return AttributeFormat::FLOAT_MATRIX42;}
template<> constexpr AttributeFormat toAttributeFormat<glm::mat4x3>(){ return AttributeFormat::FLOAT_MATRIX43;}

template<> constexpr AttributeFormat toAttributeFormat<glm::dmat2>()	{ return AttributeFormat::DOUBLE_MATRIX22;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat3>()	{ return AttributeFormat::DOUBLE_MATRIX33;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat4>()	{ return AttributeFormat::DOUBLE_MATRIX44;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat2x3>()	{ return AttributeFormat::DOUBLE_MATRIX23;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat2x4>()	{ return AttributeFormat::DOUBLE_MATRIX24;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat3x2>()	{ return AttributeFormat::DOUBLE_MATRIX32;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat3x4>()	{ return AttributeFormat::DOUBLE_MATRIX34;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat4x2>()	{ return AttributeFormat::DOUBLE_MATRIX42;}
template<> constexpr AttributeFormat toAttributeFormat<glm::dmat4x3>()	{ return AttributeFormat::DOUBLE_MATRIX43;}


struct AttributeSemantic
{
	std::string name;
	uint32_t location;
	AttributeFormat format;
};

} // namespace Rendering