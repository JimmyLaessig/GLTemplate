#pragma once
#include "GLShader.h"

class GLShaderLoader
{
public: 
	static GLSLShaderStageData LoadFile(const char* path);
};