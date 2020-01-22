#include "Rendering/GL/GL.h"
#include "Rendering/GL/GLResourceBackend.h"
#include "Rendering/GL/GLTexture2D.h"
#include "Rendering/GL/GLIndexedGeometry.h"
#include "Rendering/Renderer.h"  
#include "Rendering/Texture.h"
#include <mutex>




GLResourceBackend::GLResourceBackend()
{
	static bool glewInitialized = []()
	{
		glewExperimental = true;

		if (glewInit() == GLEW_OK)
		{
			return true;
		}
			
		return false;
	}();

	if (!glewInitialized)
	{
		throw std::exception("Failed to initialize glew!");
	}

}

std::unique_ptr<IBackendTexture> GLResourceBackend::createBackendTexture2D(ITexture * texture)
{
	return std::make_unique<GLTexture2D>(texture);
}


std::unique_ptr<IBackendIndexedGeometry> GLResourceBackend::createBackendIndexedGeometry(IndexedGeometry * geometry)
{
	return std::make_unique<GLIndexedGeometry>(geometry);
}


Renderer* GLResourceBackend::getRenderer()
{
	if (!renderer)
	{
		renderer = std::make_shared<Renderer>();
	}
	return renderer.get();
} 