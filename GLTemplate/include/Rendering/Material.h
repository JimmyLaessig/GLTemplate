#pragma once
#include "Shader.h"


class Material
{
public: 
	Shader* shader;
	UniformCollection* uniformBuffer;
};
