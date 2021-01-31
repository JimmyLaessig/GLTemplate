#include "Rendering/GL/RenderTaskImpl.h"
#include "Rendering/GL/FramebufferImpl.h"
#include "Rendering/GL/ShaderImpl.h"
#include "Rendering/GL/UniformCollectionImpl.h"
#include "Rendering/GL/PipelineStateImpl.h"
#include "Rendering/GL/RenderObjectImpl.h"
#include "Rendering/GL/IndexedMeshImpl.h"
#include "Rendering/GL/ContextImpl.h"

#include <algorithm>

namespace Rendering
{
namespace GL
{

RenderTaskImpl::RenderTaskImpl(ContextImpl::Ptr ctx):
	IRenderTask(ctx)
{}


RenderTaskImpl::Ptr
RenderTaskImpl::create(ContextImpl::Ptr context, const IRenderTask::Config& config)
{
	RenderTaskImpl::Ptr rt(new RenderTaskImpl(context));

	for (auto ro : config.mRenderObjects)
	{
		assert(context == ro->getContext());
		rt->insert(std::static_pointer_cast<RenderObjectImpl>(ro));
	}

	if (config.mFrameBuffer)
	{
		assert(context == config.mFrameBuffer->getContext());
		rt->mFrameBuffer = std::static_pointer_cast<FramebufferImpl>(config.mFrameBuffer);
	}
	else
	{
		rt->mFrameBuffer = std::static_pointer_cast<FramebufferImpl>(context->getDefaultFramebuffer());
	}

	rt->mFramebufferClearOp = config.mClearOp;

	return rt;
}


void
RenderTaskImpl::insert(RenderObjectImpl::Ptr renderObject)
{
	mRenderObjects.push_back(renderObject);

	mRenderGraph[renderObject->mRenderPass]				// Group by renderpass
				[renderObject->mPipelineState]			// Group by pipeline state
				[renderObject->mShader]					// Group by shader
				[renderObject->mIndexedMesh]			// Group by mesh
				[renderObject->mUniformCollection]++;	// Count the number of draw calls
}


void
RenderTaskImpl::execute()
{
	// Prepare the framebuffer of the RenderTask
	// Bind the framebuffer and clear it
	mFrameBuffer->bind();
	if (mFramebufferClearOp == ClearOp::ON_BIND)
	{
		mFrameBuffer->clear();
	}

	// Traverse the render graph from root to the leaves
	// Bind the different resources only once per sub-tree
	for (auto [pass, perState] : mRenderGraph)	
	for (auto [state, perShader] : perState)	
	if (state->bind())		
	for (auto [shader, perMesh] : perShader)			
	if (shader->bind())				
	for (auto [mesh, perUniformCollection] : perMesh)					
	if (mesh->bind(shader->getAttributeSemantics()))						
	for (auto [uniformCollection, numDrawCalls] : perUniformCollection)							
	if (uniformCollection->bind())							
	for (size_t i = 0; i < numDrawCalls; i++)									
	// Execute the draw command
	mesh->executeDrawCommand();

}


}
}