#pragma once
#include "System.h"

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Algorithm
{
	
	template<typename Key, typename Value>
	std::unordered_map<Value, Key> switchKeyAndValues(const std::unordered_map<Key, Value>& m)
	{
		std::unordered_map<Value, Key> res;

		for (auto& [key, value] : m)
		{
			res.emplace(value, key);
		}

		return res;
	}


	template<typename T, typename Functor>
	std::vector<T> init(size_t size, Functor fun)
	{
		std::vector<T> result(size);
		for (size_t i = 0; i < size; ++i)
		{
			result[i] = fun(i);
		}
		return result;
	}

}