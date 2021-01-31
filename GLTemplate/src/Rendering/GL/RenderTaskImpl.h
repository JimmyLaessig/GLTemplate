#pragma once

#include "Rendering/RenderTask.h"
#include "Rendering/GL/OpenGL.h"
#include "Rendering/Types.h"
#include <optional>
#include <map>

namespace Rendering
{
namespace GL
{
class ContextImpl;
class RenderObjectImpl;
class PipelineStateImpl;
class FramebufferImpl;
class RenderObjectImpl;
class UniformCollectionImpl;
class ShaderProgramImpl;
class IndexedMeshImpl;


//struct OpenGLState
//{
//
//private:
//
//	std::optional<Rendering::FaceCullingMode> cullingMode{ Rendering::FaceCullingMode() };
//
//	std::optional<Rendering::DepthTestMode> depthTestMode{ Rendering::DepthTestMode() };
//
//	std::optional<Rendering::StencilTestMode> stencilTestMode{};
//
//	std::optional<Rendering::BlendMode> blendMode{};
//
//	std::optional<Base::RectangleF> scissorTestRect{};
//
//	Base::RectangleF viewportRect{0.0f, 0.0f, 1920.f, 1080.f};
//
//public:
//
//	void setFaceCullingMode(const std::optional<Rendering::FaceCullingMode>& cullMode);
//
//
//	void setDepthTestMode(const std::optional<Rendering::DepthTestMode>& depthStencilMode);
//
//
//	void setStencilTestMode(const std::optional<Rendering::StencilTestMode>& depthStencilMode);
//
//
//	void setBlendMode(const std::optional<Rendering::BlendMode>& blendMode);
//
//
//	void setScissorTestMode(const std::optional<Base::RectangleF>& scissorRectangle);
//
//
//	void setViewport(const Base::RectangleF& viewportRectangle);
//
//
//	static OpenGLState globalOpenGLState;
//};


class RenderTaskImpl : public Rendering::IRenderTask
{

private:

	RenderTaskImpl(std::shared_ptr<ContextImpl> ctx);

public:

	using Ptr = std::shared_ptr<RenderTaskImpl>;


	static RenderTaskImpl::Ptr create(std::shared_ptr<ContextImpl> context, const IRenderTask::Config& config);


	void execute() override;


	void insert(std::shared_ptr<RenderObjectImpl> renderObject);

private:

	// 
	// Stores the render objects in  render graph optimized to minimized state changes
	// Render objects are grouped 
	//
	using PerUniformCollection	= std::map<std::shared_ptr<UniformCollectionImpl>, size_t>;
	using PerMesh				= std::map<std::shared_ptr<IndexedMeshImpl>, PerUniformCollection>;
	using PerShader				= std::map<std::shared_ptr<ShaderProgramImpl>, PerMesh>;
	using PerPipelineState		= std::map<std::shared_ptr<PipelineStateImpl>, PerShader>;
	using PerRenderPass			= std::map<uint32_t, PerPipelineState>;

	PerRenderPass mRenderGraph;

	std::vector<std::shared_ptr<RenderObjectImpl>> mRenderObjects;

	std::shared_ptr<FramebufferImpl> mFrameBuffer;

	Rendering::ClearOp mFramebufferClearOp;
};

}
}