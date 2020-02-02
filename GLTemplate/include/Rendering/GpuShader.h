#pragma once

#include "GpuResource.h"

// Forward declaration of Shader, since Shader holds a unique_ptr to IBackendShader
class Shader;


class IBackendShader : public GpuResource
{
public:
	
	IBackendShader(const Shader* shader) :
		GpuResource(),
		shader(shader)
	{}

protected:

	const Shader* shader;
};