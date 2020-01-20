#include "Rendering/GL/GLResourceBackend.h"
#include "Rendering/GL/GLTexture2D.h"
#include "Rendering/GL/GLIndexedGeometry.h"
#include "Rendering/Renderer.h"  
#include "Rendering/Texture.h"


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