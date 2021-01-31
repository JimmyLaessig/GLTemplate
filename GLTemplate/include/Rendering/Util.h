#pragma once
#include "Rendering/Types/AttributeFormat.h"
#include "Rendering/Buffer.h"

#include <concepts>

namespace Rendering
{

	inline size_t alignUp(size_t n, size_t multiple)
	{
		if (n % multiple > 0)
		{
			return n = ((n + multiple) / multiple) * multiple;
		}
		return n;
	}


	// Creates a copy of buffer with as byte vector where each row is aligned such that it's size in bytes is a multiple of alignment
	template<typename T>
	inline std::vector<std::byte> createAlignedBuffer(const std::vector<T>& buffer, size_t width, size_t height, Rendering::Alignment alignment)
	{
		assert((width * height) == buffer.size());
		
		if (buffer.empty())
		{
			return {};
		}


		static const std::unordered_map<Rendering::Alignment, size_t> mapping =
		{
			{Rendering::Alignment::BYTE,		1},
			{Rendering::Alignment::EVEN_BYTES,	2},
			{Rendering::Alignment::WORD,		4},
			{Rendering::Alignment::DOUBLE_WORD, 8}
		};

		auto widthInBytes			= width * sizeof(T);
		auto widthInBytesAligned	= alignUp(widthInBytes, mapping.at(alignment));

		std::vector<std::byte> bufferInBytes(widthInBytes * height);
		std::memcpy(bufferInBytes.data(), buffer.data(), widthInBytes * height);

		std::vector<std::byte> bufferAligned(widthInBytesAligned * height);
		for (size_t i = 0; i < height; ++i)
		{
			auto sourceScanlinePtr	= buffer.data() + i * width;
			auto targetScanlinePtr	= bufferAligned.data() + i * widthInBytesAligned;

			std::memcpy(targetScanlinePtr, sourceScanlinePtr, widthInBytes);
		}

		return bufferAligned;
	}


	template<typename T>
	IBuffer::Config makeBufferConfig(Rendering::BufferType bufferType, std::span<T> data)
	{
		return IBuffer::Config
		{
			bufferType,
			toAttributeFormat<T>(),
			data.size(),
			Base::BufferView::makeByteBufferView<T>(data)
		};
	}
}