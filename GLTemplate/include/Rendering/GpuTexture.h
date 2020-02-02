#pragma once

#include "GpuResource.h"

// Forward declaration of ITexture, since ITexture holds a unique_ptr to IBackendTexture
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