#include "Rendering/GpuResourceBackend.h"
#include "Rendering/GpuResource.h"
#include "Rendering/Renderer.h"


GpuResourceBackend* GpuResourceBackend::instance = nullptr;


bool GpuResourceBackend::registerResource(GpuResource* res)
{
	return std::get<1>(gpuResources.insert(res));
}


void GpuResourceBackend::unregisterResource(GpuResource* res)
{
	gpuResources.erase(res);
	outdatedResources.erase(res);
}


void GpuResourceBackend::markResourceOutdated(GpuResource* resource)
{
	outdatedResources.insert(resource);
}


void GpuResourceBackend::update(float deltaTime)
{
	for (auto res : outdatedResources)
	{
		res->updateGpuMemory();
	}
	outdatedResources.clear();
}


