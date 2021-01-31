#pragma once
#include "Rendering/PipelineState.h"
#include "Rendering/GL/OpenGL.h"

namespace Rendering
{
namespace GL
{
class ContextImpl;

class PipelineStateImpl : public Rendering::IPipelineState
{

private:

	PipelineStateImpl(std::shared_ptr<ContextImpl> ctx);

public:

	using Ptr = std::shared_ptr<PipelineStateImpl>;


	static std::shared_ptr<PipelineStateImpl> create(std::shared_ptr<Rendering::GL::ContextImpl> context, const IPipelineState::Config& config);


	std::shared_ptr<Rendering::GL::ContextImpl> getContextImpl();


	bool bind();
};
}
}