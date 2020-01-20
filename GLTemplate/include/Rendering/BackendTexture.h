#pragma once

#include "GpuResource.h"
#include "VectorMath.h"


class ITexture;


class IBackendTexture : public GpuResource
{
public:
	IBackendTexture(const ITexture* texture) :
		GpuResource(),
		texture(texture)
	{}
protected:
	const ITexture* texture;
};