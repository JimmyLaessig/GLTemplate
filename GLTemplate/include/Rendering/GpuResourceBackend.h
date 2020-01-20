#pragma once
#include <set>
#include <memory>

class ITexture;
class IndexedGeometry;

class Renderer;
class GpuResource;

class IBackendTexture;
class IBackendIndexedGeometry;


class GpuResourceBackend
{
public: 
	GpuResourceBackend() = default;
	

	static GpuResourceBackend * instance;

	template< class GpuResourceBackendImpl>
	static void init()
	{
		if (instance)
			delete instance;

		instance = new GpuResourceBackendImpl();
	}
	
	static GpuResourceBackend* get()
	{
		return instance;
	}


	bool registerResource(GpuResource* res);


	void unregisterResource(GpuResource* res);


	void markResourceOutdated(GpuResource* resource);


	virtual void update(float deltaTime);
	
	
	virtual Renderer* getRenderer() = 0;


	virtual std::unique_ptr<IBackendTexture> createBackendTexture2D(ITexture* texture) = 0;


	virtual std::unique_ptr<IBackendIndexedGeometry> createBackendIndexedGeometry(IndexedGeometry* geometry) = 0;

private: 

	std::set<GpuResource*> gpuResources;
	std::set<GpuResource*> outdatedResources;
};