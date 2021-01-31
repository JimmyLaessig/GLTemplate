#pragma once

#include "Rendering/internal/BaseObject.h"

#include "Rendering/Types/AttributeFormat.h"

#include <cstddef>
#include <span>
#include <memory>


namespace Base
{
	typedef std::span<std::byte> ByteBufferView;

namespace BufferView
{

template<typename T>
constexpr inline ByteBufferView 
makeByteBufferView(std::span<T> data)
{
	return Base::ByteBufferView((std::byte*)(data.data()), data.size_bytes());
}

}
}


namespace Rendering
{


ENUM_CLASS(BufferType,
	ATTRIBUTE_BUFFER,
	INDEX_BUFFER,
	UNIFORM_BUFFER
);


class GLTEMPLATE_API IBuffer : public Rendering::BaseObject
{

public:

	struct Config
	{
		BufferType type{ BufferType::ATTRIBUTE_BUFFER };

		Rendering::AttributeFormat format{ Rendering::AttributeFormat::FLOAT_VEC4 };

		// The number of elements in the buffer
		size_t numElements;

		Base::ByteBufferView data;
	};

	using Rendering::BaseObject::BaseObject;
	using Ptr = std::shared_ptr<IBuffer>;

	virtual size_t size() const = 0;


	virtual size_t sizeInBytes() const = 0;


	virtual Rendering::AttributeFormat getAttributeFormat() const = 0;


	virtual void* getNativeHandle() = 0;

};
}