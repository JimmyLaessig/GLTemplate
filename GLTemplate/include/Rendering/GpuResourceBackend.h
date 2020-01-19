#pragma once
#include <set>
#include <memory>

class Renderer;
class GpuResource;
class IndexedGeometry;
class Texture2D;
class Shader;

class GLResourceBackend;

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

//#include "Rendering/GL/GLResourceBackend.h"

//template< class GpuResourceFactory>
//class GpuResourceBackendImpl : public GpuResourceBackend
//{
//public:
//	GpuResourceBackend() : 
//		GpuResourceBackend(),
//		factory(std::make_unique<GpuResourceFactory>())
//	{}
//
//	template<class ...Args>
//	virtual Texture2D* createTexture2D(Args... args)
//	{
//		return factory->createTexture2D(args);
//	}
//
//	template<class ...Args>
//	virtual IndexedGeometry* createIndexedGeometry(Args... args)
//	{
//		return factory->createIndexedGeometry(args);
//	}
//
//private:
//
//	std::set<GpuResource*> gpuResources;
//	std::set<GpuResource*> outdatedResources;
//
//	std::unique_ptr<GpuResourceFactory> factory;
//};