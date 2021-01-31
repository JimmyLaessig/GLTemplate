#pragma once

#include "Base/Enum.h"
#include "DataType.h"
#include <cassert>

namespace Rendering
{

ENUM_CLASS(UniformType,
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

	//BOOL,
	//BOOL_VEC2,
	//BOOL_VEC3,
	//BOOL_VEC4,

	FLOAT_MATRIX22,
	FLOAT_MATRIX23,
	FLOAT_MATRIX24,
	FLOAT_MATRIX32,
	FLOAT_MATRIX33,
	FLOAT_MATRIX34,
	FLOAT_MATRIX42,
	FLOAT_MATRIX43,
	FLOAT_MATRIX44,

	TEXTURE1D,
	TEXTURE2D,
	TEXTURE3D,
	TEXTURECUBE
);


constexpr DataType
getDataType(UniformType format)
{
	switch (format)
	{
		case UniformType::FLOAT:		
		case UniformType::FLOAT_VEC2:	
		case UniformType::FLOAT_VEC3:	
		case UniformType::FLOAT_VEC4: 	
			return DataType::FLOAT32;

		case UniformType::INT:		
		case UniformType::INT_VEC2:	
		case UniformType::INT_VEC3:	
		case UniformType::INT_VEC4: 	
			return DataType::INT32;

		/*case UniformType::BOOL:			return DataType::FLOAT32;
		case UniformType::BOOL_VEC2:	return DataType::FLOAT32;
		case UniformType::BOOL_VEC3:	return DataType::FLOAT32;
		case UniformType::BOOL_VEC4: 	return DataType::FLOAT32;*/

		case UniformType::FLOAT_MATRIX22:
		case UniformType::FLOAT_MATRIX23:
		case UniformType::FLOAT_MATRIX24:
		case UniformType::FLOAT_MATRIX32:
		case UniformType::FLOAT_MATRIX33:
		case UniformType::FLOAT_MATRIX34:
		case UniformType::FLOAT_MATRIX42:
		case UniformType::FLOAT_MATRIX43:
		case UniformType::FLOAT_MATRIX44: 
			return DataType::FLOAT32;

		case UniformType::TEXTURE1D: 
		case UniformType::TEXTURE2D:
		case UniformType::TEXTURE3D:
		case UniformType::TEXTURECUBE:
			return DataType::UINT32;
	}

	assert(false);
	return DataType::FLOAT32;
}


constexpr size_t
length(UniformType channels)
{
	switch (channels)
	{
		case UniformType::FLOAT:		return 1;
		case UniformType::FLOAT_VEC2:	return 2;
		case UniformType::FLOAT_VEC3:	return 3;
		case UniformType::FLOAT_VEC4:	return 4;
	
		case UniformType::INT:			return 1;
		case UniformType::INT_VEC2:		return 2;
		case UniformType::INT_VEC3:		return 3;
		case UniformType::INT_VEC4:		return 4;

			/*case UniformType::BOOL:			return DataType::FLOAT32;
			case UniformType::BOOL_VEC2:	return DataType::FLOAT32;
			case UniformType::BOOL_VEC3:	return DataType::FLOAT32;
			case UniformType::BOOL_VEC4: 	return DataType::FLOAT32;*/

		case UniformType::FLOAT_MATRIX22: return 4;
		case UniformType::FLOAT_MATRIX23: return 6;
		case UniformType::FLOAT_MATRIX24: return 8;
		case UniformType::FLOAT_MATRIX32: return 6;
		case UniformType::FLOAT_MATRIX33: return 9;
		case UniformType::FLOAT_MATRIX34: return 12;
		case UniformType::FLOAT_MATRIX42: return 8;
		case UniformType::FLOAT_MATRIX43: return 12;
		case UniformType::FLOAT_MATRIX44: return 16;

		case UniformType::TEXTURE1D:	 return 1;
		case UniformType::TEXTURE2D:	 return 1;
		case UniformType::TEXTURE3D:	 return 1;
		case UniformType::TEXTURECUBE:	 return 1;
	};

	assert(false);
	return 0;
}


constexpr size_t
sizeInBytes(UniformType type)
{
	return length(type) * sizeInBytes(getDataType(type));
}

} // namespace Rendering