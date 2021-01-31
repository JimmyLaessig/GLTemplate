#include "Rendering/GL/PipelineStateImpl.h"

#include "Rendering/GL/ContextImpl.h"

#include <algorithm>

namespace Rendering
{
namespace GL
{


	//
	//void
	//glSetActive(GLenum cap, bool bActive)
	//{
	//	if (bActive)
	//	{
	//		glEnable(cap);
	//	}
	//	else
	//	{
	//		glDisable(cap);
	//	}
	//}
	//
	//
	//void
	//OpenGLState::setFaceCullingMode(const std::optional<Rendering::FaceCullingMode>& cullMode)
	//{
	//	if (cullMode)
	//	{
	//		glEnable(GL_CULL_FACE);
	//		glCullFace(GLPipelineState::asGLCullFace(cullMode->cullMode));
	//		glFrontFace(GLPipelineState::asGLFrontFace(cullMode->orientation));
	//	}
	//	else
	//	{
	//		glDisable(GL_CULL_FACE);
	//	}
	//
	//
	//	this->cullingMode = cullMode;
	//}
	//
	//
	//void 
	//OpenGLState::setDepthTestMode(const std::optional<Rendering::DepthTestMode>& depthTestMode)
	//{
	//	if (depthTestMode)
	//	{
	//		glEnable(GL_DEPTH_TEST);
	//		glDepthFunc(GLPipelineState::asGLDepthFunc(depthTestMode->depthFunc));
	//		glDepthMask(depthTestMode->depthMask);
	//		
	//		glDepthRange(depthTestMode->depthRange.min, depthTestMode->depthRange.max);
	//
	//		
	//		glPolygonOffset(depthTestMode->polygonOffset.factor, depthTestMode->polygonOffset.units);
	//
	//		glSetActive(GL_POLYGON_OFFSET_FILL, depthTestMode->polygonOffset.fill);
	//		glSetActive(GL_POLYGON_OFFSET_POINT, depthTestMode->polygonOffset.point);
	//		glSetActive(GL_POLYGON_OFFSET_LINE, depthTestMode->polygonOffset.line);
	//		
	//	}
	//	else
	//	{
	//		glDisable(GL_DEPTH_TEST);
	//	}
	//
	//	this->depthTestMode = depthTestMode;
	//	
	//}
	//
	//
	//void
	//OpenGLState::setStencilTestMode(const std::optional<Rendering::StencilTestMode>& stencilTestMode)
	//{
	//	if (stencilTestMode)
	//	{
	//		glEnable(GL_STENCIL_TEST);
	//
	//
	//		glStencilOpSeparate(GL_FRONT,
	//							GLPipelineState::asGLStencilOp(stencilTestMode->compareFront.stencilFail),
	//							GLPipelineState::asGLStencilOp(stencilTestMode->compareFront.depthFail),
	//							GLPipelineState::asGLStencilOp(stencilTestMode->compareFront.depthFail));
	//
	//
	//		glStencilOpSeparate(GL_BACK,
	//							GLPipelineState::asGLStencilOp(stencilTestMode->compareBack.stencilFail),
	//							GLPipelineState::asGLStencilOp(stencilTestMode->compareBack.depthFail),
	//							GLPipelineState::asGLStencilOp(stencilTestMode->compareBack.depthFail));
	//
	//
	//		glStencilFuncSeparate(GL_FRONT,
	//							  GLPipelineState::asGLStencilFunc(stencilTestMode->operationFront.func),
	//							  stencilTestMode->operationFront.ref,
	//							  stencilTestMode->operationFront.mask);
	//		
	//
	//		glStencilFuncSeparate(GL_BACK,
	//							  GLPipelineState::asGLStencilFunc(stencilTestMode->operationBack.func),
	//							  stencilTestMode->operationBack.ref,
	//							  stencilTestMode->operationBack.mask);
	//	}
	//	else
	//	{
	//		glDisable(GL_DEPTH_TEST);
	//	}
	//
	//	this->stencilTestMode = stencilTestMode;
	//}
	//
	//
	//void 
	//OpenGLState::setBlendMode(const std::optional<Rendering::BlendMode>& blendMode)
	//{
	//	
	//	if (blendMode)
	//	{
	//		glEnable(GL_BLEND);
	//
	//		glBlendFunc(GLPipelineState::asGLBlendFactor(blendMode->sourceFactor), 
	//					GLPipelineState::asGLBlendFactor(blendMode->destFactor));
	//		glBlendEquation(GLPipelineState::asGLBlendEquation(blendMode->blendFunc));
	//	}
	//	else
	//	{
	//		glDisable(GL_BLEND);
	//
	//	}
	//	this->blendMode = blendMode;
	//}
	//
	//
	//void 
	//OpenGLState::setScissorTestMode(const std::optional<Base::RectangleF>& scissorRectangle)
	//{
	//	if (scissorRectangle)
	//	{
	//		glEnable(GL_SCISSOR_TEST);
	//		glScissor(scissorRectangle->mX, scissorRectangle->mY, scissorRectangle->mWidth, scissorRectangle->mHeight);
	//	}
	//	else
	//	{
	//		glDisable(GL_SCISSOR_TEST);
	//	}
	//	this->scissorTestRect = scissorRectangle;
	//}
	//
	//
	//void
	//OpenGLState::setViewport(const Base::RectangleF& viewportRectangle)
	//{
	//	glViewport(viewportRectangle.mX, viewportRectangle.mY, viewportRectangle.mWidth, viewportRectangle.mHeight);
	//
	//	this->viewportRect = viewportRectangle;
	//}



PipelineStateImpl::PipelineStateImpl(ContextImpl::Ptr ctx) :
	Rendering::IPipelineState(ctx)
{}


std::shared_ptr<PipelineStateImpl>
PipelineStateImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, const IPipelineState::Config& config)
{
	
	std::shared_ptr<PipelineStateImpl> pipelineState(new PipelineStateImpl(context));

	return pipelineState;
}


std::shared_ptr<Rendering::GL::ContextImpl> 
PipelineStateImpl::getContextImpl()
{
	return std::static_pointer_cast<Rendering::GL::ContextImpl>(getContext());
}


bool
PipelineStateImpl::bind()
{
	// TODO
	return true;
}

} // namespace GL
} // namespace Rendering