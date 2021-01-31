#pragma once

#include "Base/System.h"

#include "Base/UUID2.h"
#include "Base/NonCopyable.h"

#include "Rendering/Types.h"

#include "Rendering/Buffer.h"
#include "Rendering/IndexedMesh.h"
#include "Rendering/Framebuffer.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"
#include "Rendering/UniformCollection.h"
#include "Rendering/RenderObject.h"
#include "Rendering/RenderTask.h"
#include "Rendering/PipelineState.h"

#include <memory>


namespace Rendering
{

ENUM_CLASS(GraphicsAPI,
	OPENGL,
	VULKAN,
);


class GLTEMPLATE_API IContext : public Base::NonCopyable, public std::enable_shared_from_this<IContext>
{

public:

	using Ptr = std::shared_ptr<IContext>;


	virtual ~IContext() = default;


	virtual GraphicsAPI getGraphicsAPI() const = 0;


	virtual IBuffer::Ptr createBuffer(const IBuffer::Config& config) = 0;


	virtual IIndexedMesh::Ptr createIndexedMesh(const IIndexedMesh::Config& config) = 0;


	virtual ITexture2D::Ptr createTexture2D(const ITexture2D::Config& config) = 0;


	virtual IShaderProgram::Ptr createShaderProgram(const IShaderProgram::Config& config) = 0;


	virtual IUniformCollection::Ptr createUniformCollection(IShaderProgram::Ptr shader) = 0;


	virtual IPipelineState::Ptr createPipelineState(const IPipelineState::Config& config) = 0;


	virtual IRenderObject::Ptr createRenderObject(const IRenderObject::Config& config) = 0;


	virtual IRenderTask::Ptr createRenderTask(const IRenderTask::Config& config) = 0;


	virtual IFramebufferObject::Ptr createFramebuffer(const IFramebufferObject::Config& config) = 0;


	virtual IFramebufferObject::Ptr getDefaultFramebuffer() = 0;


	virtual Rendering::Alignment getTextureRowAlignment() const = 0;

};
}