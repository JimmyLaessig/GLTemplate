#include "Rendering/GL/RenderObjectImpl.h"
#include "Rendering/GL/IndexedMeshImpl.h"
#include "Rendering/GL/ShaderImpl.h"
#include "Rendering/GL/PipelineStateImpl.h"
#include "Rendering/GL/UniformCollectionImpl.h"

#include "Rendering/GL/ContextImpl.h"

#include "Rendering/GL/internal/GLTypes.h"
#include <algorithm>

namespace Rendering
{
namespace GL
{

RenderObjectImpl::RenderObjectImpl(ContextImpl::Ptr ctx) :
	Rendering::IRenderObject(ctx)
{}


std::shared_ptr<RenderObjectImpl> 
RenderObjectImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, const IRenderObject::Config& config)
{
	// Ensure that the linked objects are created from the same context
	{
		assert(config.shader);
		assert(config.pipelineState);
		assert(config.mesh);
		assert(context == config.shader->getContext());
		assert(context == config.pipelineState->getContext());
		assert(context == config.mesh->getContext());
		if (config.uniforms) { assert(context == config.uniforms->getContext()); };
	}

	// Create the render object
	std::shared_ptr<RenderObjectImpl> renderObject(new RenderObjectImpl(context));
	renderObject->mPipelineState		= std::static_pointer_cast<PipelineStateImpl>(config.pipelineState);
	renderObject->mShader				= std::static_pointer_cast<ShaderProgramImpl>(config.shader);
	renderObject->mUniformCollection	= std::static_pointer_cast<UniformCollectionImpl>(config.uniforms);
	renderObject->mIndexedMesh			= std::static_pointer_cast<IndexedMeshImpl>(config.mesh);
	renderObject->mRenderPass			= config.renderPass;

	return renderObject;
}


std::shared_ptr<Rendering::GL::ContextImpl>
RenderObjectImpl::getContextImpl()
{
	return std::static_pointer_cast<Rendering::GL::ContextImpl>(getContext());
}


} // namespace GL
} // namespace Rendering