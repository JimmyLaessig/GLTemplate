#pragma once
#include "Base/Enum.h"

#include <cassert>

namespace Rendering
{
	ENUM_CLASS(DataType,
		INT8,
		UINT8,
		INT16,
		UINT16,
		INT32,
		UINT32,
		FLOAT16,
		FLOAT32,
		DOUBLE,
	);


	constexpr size_t sizeInBytes(DataType type)
	{
		switch(type)
		{
			case DataType::INT8:	return 1;
			case DataType::UINT8:	return 1;
			case DataType::INT16:	return 2;
			case DataType::UINT16:	return 2;
			case DataType::INT32:	return 4;
			case DataType::UINT32:	return 4;
			case DataType::FLOAT16: return 2;
			case DataType::FLOAT32:	return 4;
			case DataType::DOUBLE:	return 8;
		};

		assert(false);
		return 0;
	}

	
	template<typename T>
	constexpr Rendering::DataType 
	asDataType()
	{	
		static_assert(false); return {};
	}


	template<> constexpr Rendering::DataType asDataType<uint8_t>()  { return DataType::UINT8;	}
	template<> constexpr Rendering::DataType asDataType<int8_t>()	{ return DataType::INT8;	}
	template<> constexpr Rendering::DataType asDataType<uint16_t>() { return DataType::UINT16;	}
	template<> constexpr Rendering::DataType asDataType<int16_t>()  { return DataType::INT16;	}
	template<> constexpr Rendering::DataType asDataType<int32_t>()  { return DataType::INT32;	}
	template<> constexpr Rendering::DataType asDataType<uint32_t>() { return DataType::UINT32;	}
	template<> constexpr Rendering::DataType asDataType<float>()	{ return DataType::FLOAT32; }
	template<> constexpr Rendering::DataType asDataType<double>()	{ return DataType::DOUBLE;	}


}