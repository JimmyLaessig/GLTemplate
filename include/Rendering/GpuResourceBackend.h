#pragma once
#include <set>
#include <memory>


class Renderer;
class GpuResource;
class DrawableGpuResource;

class GpuResourceBackend
{
public: 
	GpuResourceBackend() = default;


	static GpuResourceBackend* get()
	{
		static GpuResourceBackend backend;
		return &backend;
	}


	bool registerResource(GpuResource* res);


	bool registerResource(DrawableGpuResource* res);


	void unregisterResource(GpuResource* res);


	void unregisterResource(DrawableGpuResource* res);


	void markResourceOutdated(GpuResource* resource);


	Renderer* getRenderer();


	virtual void update(float deltaTime);

private: 
	// Should be a unqiue_ptr but forward-declarated type does not allow for this (without double constructors)
	std::shared_ptr<Renderer> renderer;

	std::set<GpuResource*> gpuResources;
	std::set<GpuResource*> outdatedResources;
	std::set<DrawableGpuResource*> drawableGpuResources;
};