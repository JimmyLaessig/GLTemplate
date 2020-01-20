#pragma once

#include "GpuResource.h"
#include "Material.h"


class IBackendIndexedGeometry : public GpuResource
{
public:

	IBackendIndexedGeometry(const IndexedGeometry* geometry) :
		GpuResource(),
		geometry(geometry)
	{}

protected:

	const IndexedGeometry* geometry;
};