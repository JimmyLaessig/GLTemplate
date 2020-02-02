#pragma once
#include "GLShader.h"

class GLSLShaderParser
{
public: 
	static GLSLShaderStageData Parse(const std::string_view code);
};