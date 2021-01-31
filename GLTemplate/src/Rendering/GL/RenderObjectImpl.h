#pragma once

#include "Rendering/RenderObject.h"
#include "Rendering/GL/OpenGL.h"


namespace Rendering
{
namespace GL
{
class ContextImpl;
class IndexedMeshImpl;
class ShaderProgramImpl;
class PipelineStateImpl;
class UniformCollectionImpl;

class RenderTaskImpl;


class RenderObjectImpl : public Rendering::IRenderObject
{
	friend class RenderTaskImpl;
private:

	RenderObjectImpl(std::shared_ptr<ContextImpl> ctx);

public:

	using Ptr = std::shared_ptr<RenderObjectImpl>;


	static RenderObjectImpl::Ptr create(std::shared_ptr<ContextImpl> context, const IRenderObject::Config& config);


	std::shared_ptr<ContextImpl> getContextImpl();

private:

	std::shared_ptr<ShaderProgramImpl> mShader;
	
	std::shared_ptr<UniformCollectionImpl> mUniformCollection;

	std::shared_ptr<PipelineStateImpl> mPipelineState;

	std::shared_ptr<IndexedMeshImpl> mIndexedMesh;

	uint32_t mRenderPass{0};

};
}
}