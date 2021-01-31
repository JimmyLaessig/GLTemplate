#pragma once

#include "System.h"
#include "Base/StringUtil.h"

#include <optional>
#include <vector>


namespace internal
{
	inline std::vector<std::string> GLTEMPLATE_API VA_ARGS_SPLIT(const std::string_view s)
	{
		std::vector<std::string> words = Base::stringSplit(s, ',');

		std::vector<std::string> result;
		for (auto& word : words)
		{
			if (!word.empty())
			{
				result.push_back(Base::removeTrailingWhiteSpaces(word));
			}
		}

		return result;
	}
}

namespace EnumTools
{
	template<typename ENUM_TYPE>
	inline std::optional<ENUM_TYPE> stringToEnum(const std::string_view s)
	{
		return {};
	}
}

#define ENUM_CLASS(ENUM_NAME, ...)																	\
																									\
enum class ENUM_NAME																				\
{																									\
	__VA_ARGS__																						\
};																									\
namespace																							\
{																									\
	inline const std::vector<std::string> ENUM_NAME##Names = internal::VA_ARGS_SPLIT(#__VA_ARGS__);	\
}																									\
																									\
inline const std::string_view GLTEMPLATE_API enumToString(ENUM_NAME e)								\
{																									\
	return ENUM_NAME##Names[(size_t)e];																\
}																									\
																									\
inline std::optional < ENUM_NAME > GLTEMPLATE_API stringTo##ENUM_NAME(const std::string_view e)		\
{																									\
	auto& enumNames = ENUM_NAME##Names;																\
																									\
	auto it = std::find_if(enumNames.begin(), enumNames.end(), [&](const auto& s)					\
	{																								\
		return e == s;																				\
	});																								\
	if (it == enumNames.end())																		\
	{																								\
		return {};																					\
	}																								\
																									\
	auto index = std::distance(it, enumNames.begin());												\
																									\
	return ( ENUM_NAME )index;																		\
}																									\