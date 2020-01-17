
#pragma once
#include "GpuResource.h"
#include "SharedAsset.h"

class Shader : public GpuResource, public SharedAsset
{
public:

	virtual void bind() = 0;

};

class UniformCollection
{

};