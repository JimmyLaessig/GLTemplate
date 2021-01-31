#pragma once

#include "Rendering/GL/ContextImpl.h"

#include "Rendering/GL/BufferImpl.h"
#include "Rendering/GL/IndexedMeshImpl.h"
#include "Rendering/GL/Texture2DImpl.h"
#include "Rendering/GL/ShaderImpl.h"
#include "Rendering/GL/UniformCollectionImpl.h"
#include "Rendering/GL/RenderObjectImpl.h"
#include "Rendering/GL/RenderTaskImpl.h"
#include "Rendering/GL/FramebufferImpl.h"
#include "Rendering/GL/PipelineStateImpl.h"

#include "Rendering/GL/internal/GLDebugMessageCallback.h"

#include <glm/glm.hpp>

#include <mutex>
#include <iostream>
#include <memory>


namespace Rendering
{
namespace GL
{
namespace
{
	std::mutex contextInitProtection;
	bool glewInitialized{ false };

	bool initializeGLEW()
	{

		std::scoped_lock lock(contextInitProtection);

		glewExperimental = true;
		glewInitialized = glewInit() == GLEW_OK;

		if (glewInitialized)
		{
			glGetError();
		}

		return glewInitialized;
	}
}


std::shared_ptr<Rendering::GL::ContextImpl>
ContextImpl::create(std::shared_ptr<GLFWwindow> nativeWindowHandle)
{
	if (!nativeWindowHandle)
	{
		return nullptr;
	}

	glfwMakeContextCurrent(nativeWindowHandle.get());

	if (!initializeGLEW())
	{
		return nullptr;
	}

	ContextImpl::Ptr context(new ContextImpl);

	context->mWindowHandle = nativeWindowHandle;
	
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugMessageCallback, 0);

	
	return context;
}


std::shared_ptr<ContextImpl>
ContextImpl::asShared()
{
	auto ptr = shared_from_this();

	return std::static_pointer_cast<ContextImpl>(ptr);
}


Rendering::Alignment
ContextImpl::getTextureRowAlignment() const
{
	//GLint alignment = 0;
	//glGetIntegerv(GL_PACK_ALIGNMENT, &alignment);

	// TODO implement correctly
	return Rendering::Alignment::WORD;
}


Rendering::IBuffer::Ptr
ContextImpl::createBuffer(const IBuffer::Config& config)				
{																																		
	auto buffer = Rendering::GL::BufferImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::IBuffer>(buffer);		
}


Rendering::IIndexedMesh::Ptr
ContextImpl::createIndexedMesh(const IIndexedMesh::Config& config)
{
	auto mesh = Rendering::GL::IndexedMeshImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::IIndexedMesh>(mesh);
}


Rendering::ITexture2D::Ptr
ContextImpl::createTexture2D(const ITexture2D::Config& config)				
{																																					
	auto texture = Rendering::GL::Texture2DImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::ITexture2D>(texture);		
}	


Rendering::IShaderProgram::Ptr
ContextImpl::createShaderProgram(const IShaderProgram::Config& config)
{
	auto shader	= Rendering::GL::ShaderProgramImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::IShaderProgram>(shader);
}


IUniformCollection::Ptr
ContextImpl::createUniformCollection(IShaderProgram::Ptr shader)
{
	auto shaderGL	= std::static_pointer_cast<ShaderProgramImpl>(shader);
	auto collection = Rendering::GL::UniformCollectionImpl::create(asShared(), shaderGL);
	return std::static_pointer_cast<Rendering::IUniformCollection>(collection);
}


IPipelineState::Ptr
ContextImpl::createPipelineState(const IPipelineState::Config& config)
{
	auto task = Rendering::GL::PipelineStateImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::IPipelineState>(task);
}


IRenderObject::Ptr 
ContextImpl::createRenderObject(const IRenderObject::Config& config)
{
	auto renderObject = Rendering::GL::RenderObjectImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::IRenderObject>(renderObject);
}


IRenderTask::Ptr
ContextImpl::createRenderTask(const IRenderTask::Config& config)
{
	auto task = Rendering::GL::RenderTaskImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::IRenderTask>(task);
}


IFramebufferObject::Ptr 
ContextImpl::createFramebuffer(const IFramebufferObject::Config& config)
{
	auto framebuffer = Rendering::GL::FramebufferImpl::create(asShared(), config);
	return std::static_pointer_cast<Rendering::IFramebufferObject>(framebuffer);
}


IFramebufferObject::Ptr 
ContextImpl::getDefaultFramebuffer()
{
	if (!mDefaultFramebuffer)
	{
		mDefaultFramebuffer = Rendering::GL::FramebufferImpl::createDefaultFramebuffer(asShared());
	}
	return std::static_pointer_cast<Rendering::IFramebufferObject>(mDefaultFramebuffer);
}


}
}