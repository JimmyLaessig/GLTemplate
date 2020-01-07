#include "GpuResource.h"
#include "GpuResourceBackend.h"
//GpuResource::GpuResource(GpuResource && other) noexcept : 
//	bIsOutdated(other.bIsOutdated), 
//	gpuResourceLock(std::move(other.getResourceLock))
//{
//	other.bIsOutdated = false;
//}


GpuResource::GpuResource()
{
	if (auto backend = getGpuResourceBackend())
	{
		backend->registerResource(this);
	}
}

GpuResource::~GpuResource()
{
	if (auto backend = getGpuResourceBackend())
	{
		backend->unregisterResource(this);
	}
}

GpuResourceBackend * GpuResource::getGpuResourceBackend()
{
	return GpuResourceBackend::get();
}


