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

	template<class ...Args>
	Texture2D* createTexture2D(Args... args)
	{
		return nullptr;
		//new GLTexture2D(args...);
	}

	template<class ...Args>
	IndexedGeometry* createIndexedGeometry(Args... args)
	{
		return nullptr;
		//new GLIndexedGeometry(args...);
	}


	virtual Renderer* getRenderer() override;

private: 
	std::shared_ptr<Renderer> renderer;
};

