#pragma once
#include <set>
#include <memory>

class Renderer;
class GpuResource;
class IndexedGeometry;
class Texture2D;
class Shader;


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


	virtual Renderer* getRenderer() = 0;


	virtual void update(float deltaTime);


	template<class ...Args>
	Texture2D* createTexture2D(Args... args) = 0;
	template<class ...Args>
	IndexedGeometry* createIndexedGeometry(Args... args) = 0;

private: 

	std::set<GpuResource*> gpuResources;
	std::set<GpuResource*> outdatedResources;
};