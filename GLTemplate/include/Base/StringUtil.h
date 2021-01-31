#pragma once

#include "System.h"
#include <string_view>
#include <string>
#include <vector>
#include <cctype>

namespace Base
{
	inline std::vector<std::string> GLTEMPLATE_API stringSplit(const std::string_view s, char delimiter)
	{
		std::vector<std::string> words;

		size_t wordBegin = 0;

		for (size_t i = 0; i < s.size(); ++i)
		{
			// Emit new word
			if (s[i] == delimiter)
			{
				words.emplace_back(s.data() + wordBegin, i - wordBegin);
				wordBegin = i + 1;
			}

			if (i == s.size() - 1)
			{
				words.emplace_back(s.data() + wordBegin, i - wordBegin + 1);
			}
		}

		return words;
	}


	inline std::string GLTEMPLATE_API removeTrailingWhiteSpaces(const std::string_view s)
	{
		size_t startIncl = 0;
		size_t endIncl = s.size() - 1;

		while (isspace(s[startIncl]) && startIncl < s.size())
		{
			++startIncl;
		}

		while (isspace(s[endIncl]) && endIncl >= 0)
		{
			--endIncl;
		}

		if (startIncl < s.size() && endIncl >= startIncl)
		{
			return std::string(s.data() + startIncl, endIncl - startIncl + 1);
		}
		else
		{
			return "";
		}
	}
}