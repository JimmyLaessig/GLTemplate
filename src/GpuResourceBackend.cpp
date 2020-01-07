#include "GpuResourceBackend.h"
#include "GpuResource.h"
#include "Renderer.h"

bool GpuResourceBackend::registerResource(GpuResource* res)
{
	return std::get<1>(gpuResources.insert(res));
}


bool GpuResourceBackend::registerResource(DrawableGpuResource* res)
{

	if (std::get<1>(gpuResources.insert(res)) && std::get<1>(drawableGpuResources.insert(res)))
	{
		return true;
	}
	unregisterResource(res);
	// TODO LOG ERROR
	return false;
}


void GpuResourceBackend::unregisterResource(GpuResource* res)
{
	gpuResources.erase(res);
	outdatedResources.erase(res);
}


void GpuResourceBackend::unregisterResource(DrawableGpuResource* res)
{
	gpuResources.erase(res);
	outdatedResources.erase(res);
	drawableGpuResources.erase(res);
}


void GpuResourceBackend::markResourceOutdated(GpuResource* resource)
{
	outdatedResources.insert(resource);
}


Renderer * GpuResourceBackend::getRenderer()
{
	if (!renderer)
	{
		renderer = std::make_shared<Renderer>();// Renderer();
	}
	return renderer.get();
} 


void GpuResourceBackend::update(float deltaTime)
{
	for (auto res : outdatedResources)
	{
		res->updateGpuMemory();
	}
	outdatedResources.clear();
}


