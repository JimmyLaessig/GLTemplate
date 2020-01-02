#pragma once
#include "GLSLShader.h"

class GLSLShaderLoader
{
public: 
	static ShaderStageData LoadFile(const char* path);
};