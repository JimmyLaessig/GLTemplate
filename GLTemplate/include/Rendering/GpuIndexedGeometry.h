#pragma once

#include "GpuResource.h"

// Forward declaration of IndexedGeometry, since IndexedGeometry holds a unique_ptr to IBackendIndexedGeometry
class IndexedGeometry;


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