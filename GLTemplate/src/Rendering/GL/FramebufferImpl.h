#pragma once

#include "Rendering/Framebuffer.h"
#include "Rendering/GL/OpenGL.h"


#include <vector>
#include <optional>


namespace Rendering
{
namespace GL
{
class ContextImpl;

class FramebufferImpl : public Rendering::IFramebufferObject
{

private:

	FramebufferImpl(std::shared_ptr<ContextImpl> ctx);

public: 

	~FramebufferImpl();


	using Ptr = std::shared_ptr<FramebufferImpl>;


	static FramebufferImpl::Ptr create(std::shared_ptr<ContextImpl> context, const Rendering::IFramebufferObject::Config& shader);


	static FramebufferImpl::Ptr createDefaultFramebuffer(std::shared_ptr<ContextImpl> context);


	std::shared_ptr<ContextImpl> getContextImpl();


	GLuint getFBOHandle();


	virtual void clear();


	virtual bool bind();


	virtual std::shared_ptr<ITexture2D> getDepthStencilAttachment() override;


	virtual std::shared_ptr<ITexture2D> getColorAttachment(size_t index) override;

protected:

	GLuint mFBOHandle{ 0 };

	std::vector<ColorAttachment> mColorAttachments;

	std::optional<DepthStencilAttachment> mDepthStencilAttachment;

	bool populateFBO();

};
}
}