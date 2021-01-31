#pragma once
#include "Rendering/Context.h"

#include "Rendering/GL/OpenGL.h"


namespace Rendering
{
namespace GL
{
class FramebufferImpl;

class GLTEMPLATE_API ContextImpl : public Rendering::IContext
{
	
public:

	using Ptr = std::shared_ptr<ContextImpl>;


	static std::shared_ptr<ContextImpl> create(std::shared_ptr<GLFWwindow> nativeWindowHandle);


	Rendering::GraphicsAPI getGraphicsAPI() const override { return Rendering::GraphicsAPI::OPENGL; }


	GLFWwindow* getNativeWindowHandle() { return mWindowHandle.get(); }


	IBuffer::Ptr createBuffer(const IBuffer::Config& config) override;


	IIndexedMesh::Ptr createIndexedMesh(const IIndexedMesh::Config& config) override;


	ITexture2D::Ptr createTexture2D(const ITexture2D::Config& config) override;


	IShaderProgram::Ptr createShaderProgram(const IShaderProgram::Config& config) override;


	IUniformCollection::Ptr createUniformCollection(IShaderProgram::Ptr shader) override;


	IPipelineState::Ptr createPipelineState(const IPipelineState::Config& config) override;


	IRenderObject::Ptr createRenderObject(const IRenderObject::Config& config) override;


	IRenderTask::Ptr createRenderTask(const IRenderTask::Config& config) override;


	IFramebufferObject::Ptr createFramebuffer(const IFramebufferObject::Config& config) override;


	IFramebufferObject::Ptr getDefaultFramebuffer() override;


	Rendering::Alignment getTextureRowAlignment() const override;

private:

	std::shared_ptr<ContextImpl> asShared();

	std::shared_ptr<GLFWwindow> mWindowHandle{nullptr};

	std::shared_ptr<Rendering::GL::FramebufferImpl> mDefaultFramebuffer{ nullptr };
};
}
}