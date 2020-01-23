#include "Rendering/GL/GL.h"
#include "Rendering/GL/GLResourceBackend.h"
#include "Rendering/GL/GLTexture2D.h"
#include "Rendering/GL/GLIndexedGeometry.h"
#include "Rendering/GL/GLShader.h"
#include "Rendering/Renderer.h"  

#include "Components/Texture.h"
#include "Components/Shader.h"

#include <mutex>


void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "OpenGL Error occured: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}


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

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

}

std::unique_ptr<IBackendTexture> GLResourceBackend::createBackendTexture2D(ITexture * texture)
{
	return std::make_unique<GLTexture2D>(texture);
}


std::unique_ptr<IBackendIndexedGeometry> GLResourceBackend::createBackendIndexedGeometry(IndexedGeometry * geometry)
{
	return std::make_unique<GLIndexedGeometry>(geometry);
}

std::unique_ptr<IBackendShader> GLResourceBackend::createBackendShader(Shader * geometry)
{
	return std::make_unique<GLShader>(geometry);
}


Renderer* GLResourceBackend::getRenderer()
{
	if (!renderer)
	{
		renderer = std::make_shared<Renderer>();
	}
	return renderer.get();
} 