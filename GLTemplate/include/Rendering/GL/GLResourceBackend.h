#pragma once
#include <set>
#include <memory>
#include "../GpuResourceBackend.h"

#include "GLTexture2D.h"
#include "GLIndexedGeometry.h"


class GLResourceBackend : public GpuResourceBackend
{
public: 

	GLResourceBackend() = default;


	virtual Renderer* getRenderer() override;


	template<class ...Args>
	Texture2D* createTexture2D(Args... args)
	{
		new GLTexture2D(args);
	}

	template<class ...Args>
	IndexedGeometry* createIndexedGeometry(Args... args)
	{
		new GLIndexedGeometry(args);
	}


private: 
	// Should be a unqiue_ptr but forward-declarated type does not allow for this (without double constructors)
	std::shared_ptr<Renderer> renderer;

	std::set<GpuResource*> gpuResources;
	std::set<GpuResource*> outdatedResources;
	//std::set<DrawableGpuResource*> drawableGpuResources;
};