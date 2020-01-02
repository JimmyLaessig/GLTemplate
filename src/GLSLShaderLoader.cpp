#include "GLSLShaderLoader.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <assert.h>
#include <optional>
#include <iostream>

std::optional<std::string> getShaderStageCode(const std::string& code, const std::string& shaderStage)
{

	std::regex matchAnyStage("^\\s*#ifdef\\s*[VERTEX|FRAGMENT|GEOMETRY|TESSELLATION_EVALUATION|TESSELLATION_CONTROL|COMPUTE]*_STAGE\\s*");
	std::regex matchTargetStage("^\\s*#ifdef\\s*" + shaderStage + "_STAGE\\s*");
	std::regex matchStageEnd("^\\s*#endif\\s*");

	bool StageFound				= false;
	bool bInShaderStage			= false;
	bool bInCorrectShaderStage	= false;

	std::stringstream ss(code);
	std::stringstream shaderCode;

	for (std::string line; std::getline(ss, line);)
	{		
		if (bInShaderStage)
		{
			if (std::regex_match(line, matchStageEnd))
			{
				bInShaderStage			= false;
				bInCorrectShaderStage	= false;
			}
			if (bInCorrectShaderStage)
			{
				shaderCode << line << std::endl;
			}
		}
		else
		{
			if (std::regex_match(line, matchTargetStage))
			{
				bInShaderStage			= true;
				bInCorrectShaderStage	= true;
				StageFound				= true;
			}
			else if (std::regex_match(line, matchAnyStage))
			{
				bInShaderStage			= true;
				bInCorrectShaderStage	= false;
			}
			else
			{
				shaderCode << line << std::endl;
			}
		}	
	}

	return StageFound ? shaderCode.str() : std::optional<std::string>();
}


ShaderStageData GLSLShaderLoader::LoadFile(const char* path)
{
	
	std::ifstream file(path);
	if (!file.good())
	{
		return {};
	}
	std::string code = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	return ShaderStageData
	{
		getShaderStageCode(code, "VERTEX").value_or(""),
		getShaderStageCode(code, "FRAGMENT").value_or(""),
		getShaderStageCode(code, "GEOMETRY").value_or(""),
		getShaderStageCode(code, "TESSELLATION_CONTROL").value_or(""),
		getShaderStageCode(code, "TESSELLATION_EVALUATION").value_or(""),
		getShaderStageCode(code, "COMPUTE").value_or(""),
	};
}