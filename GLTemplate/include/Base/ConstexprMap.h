#pragma once
#include "System.h"
#include <array>

namespace Base
{

template<typename Key, typename Value, std::size_t Size>
struct GLTEMPLATE_API ConstexprMap
{
public:

	constexpr ConstexprMap(std::initializer_list<std::pair<Key, Value>> data) :
		mData(data)
	{}

	[[nodiscard]] constexpr const Value& 
	at(const Key& key) const
	{
		const auto itr = std::find_if(mData.begin(),
			mData.end(),
			[&key](const auto& pair) { return pair.first == key; });

		if (itr != mData.end())
		{
			return itr->second;
		}

		throw std::range_error("Not found");
	}


	constexpr const Value&
	operator[](const Key& key) const
	{
		return at(key);
	}

private:

	std::array<std::pair<Key, Value>, Size> mData;
};
}