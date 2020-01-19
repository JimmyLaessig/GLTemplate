#include "Rendering/GL/GLResourceBackend.h"
#include "Rendering/Renderer.h"  


Renderer* GLResourceBackend::getRenderer()
{
	if (!renderer)
	{
		renderer = std::make_shared<Renderer>();// Renderer();
	}
	return renderer.get();
} 