#include "Rendering/GL/FramebufferImpl.h"
#include "Rendering/GL/Texture2DImpl.h"

#include "Rendering/GL/ContextImpl.h"
#include "OpenGL.h"
//#include "Rendering/GL/GLTypes.h"
//#include "Rendering/Util.h"
#include "Base/Algorithm.h"

namespace Rendering
{
namespace GL
{


FramebufferImpl::FramebufferImpl(ContextImpl::Ptr ctx) :
	Rendering::IFramebufferObject(ctx)
{}


FramebufferImpl::~FramebufferImpl()
{
	glDeleteFramebuffers(1, &mFBOHandle);
}


std::shared_ptr<FramebufferImpl>
FramebufferImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, const Rendering::IFramebufferObject::Config& config)
{
	std::shared_ptr<FramebufferImpl> framebuffer(new FramebufferImpl(context));

	framebuffer->mColorAttachments			= config.colorAttachments;
	framebuffer->mDepthStencilAttachment	= config.depthStencilAttachment;
	
	if (!framebuffer->populateFBO())
	{
		return nullptr;
	}

	return framebuffer;
}


std::shared_ptr<FramebufferImpl> 
FramebufferImpl::createDefaultFramebuffer(std::shared_ptr<Rendering::GL::ContextImpl> context)
{	
	std::shared_ptr<FramebufferImpl> framebuffer(new FramebufferImpl(context));

	framebuffer->mFBOHandle					= 0;
	framebuffer->mColorAttachments			= { ColorAttachment{.texture = nullptr, .clearColor = {0.0f, 0.0f, 0.0f, 1.0f}} };
	framebuffer->mDepthStencilAttachment	= DepthStencilAttachment{ .texture = nullptr, .clearDepth = 1.0f, .clearStencil = 0 };

	return framebuffer;		
}

bool
FramebufferImpl::populateFBO()
{
	// Create the OpenGL FBO handle
	{
		if (mFBOHandle > 0)
			glDeleteFramebuffers(1, &mFBOHandle);

		// Create the framebuffer handle
		glGenFramebuffers(1, &mFBOHandle);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, mFBOHandle);

	// Attach each attachment to the FBO
	if (mDepthStencilAttachment)
	{
		auto format = mDepthStencilAttachment->texture->getTextureFormat();

		if (!std::holds_alternative<Rendering::DepthFormat>(format))
		{
			// TODO Log error
			return false;
		}

		auto textureHandle = std::static_pointer_cast<Texture2DImpl>(mDepthStencilAttachment->texture)->getTextureHandle();

		glFramebufferTexture2D(GL_FRAMEBUFFER,
							   GL_DEPTH_ATTACHMENT,
							   GL_TEXTURE_2D,
							   textureHandle,
							   0);
	}

	// Attach each color attachment
	uint32_t i = 0;
	for (auto& colorAttachment : mColorAttachments)
	{
		auto format = colorAttachment.texture->getTextureFormat();

		if (!std::holds_alternative<Rendering::ColorFormat>(format))
		{
			// TODO Log error
			return false;
		}

		auto textureHandle = std::static_pointer_cast<Texture2DImpl>(colorAttachment.texture)->getTextureHandle();

		glFramebufferTexture2D(GL_FRAMEBUFFER,
							   GL_COLOR_ATTACHMENT0 + i,
							   GL_TEXTURE_2D,
							   textureHandle,
							   0);
		i++;
	}
	
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}


Rendering::GL::ContextImpl::Ptr
FramebufferImpl::getContextImpl()
{
	return std::static_pointer_cast<Rendering::GL::ContextImpl>(getContext());
}


bool
FramebufferImpl::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFBOHandle);

	std::vector<GLenum> buffers;

	// To render to the default framebuffer
	// double-buffered context: GL_BACK 
	// single-buffered context: GL_FRONT
	// TODO support single-buffered context
	// If not color attachmnte are present, buffers will be empty and
	// glDrawBuffers will set all attachments >= n to GL_NONE
	if (mFBOHandle == 0)
	{
		buffers = { GL_BACK };
	}
	else 
	{
		buffers = Algorithm::init<GLenum>(mColorAttachments.size(), [](size_t index)
		{
			return GL_COLOR_ATTACHMENT0 + index;
		});
	}

	glDrawBuffers(buffers.size(), buffers.data());

	return true;
}


GLuint 
FramebufferImpl::getFBOHandle()
{
	return mFBOHandle;
}


void
FramebufferImpl::clear()
{
	if (mDepthStencilAttachment)
	{
		glClearDepth(mDepthStencilAttachment->clearDepth);
		glClearStencil(mDepthStencilAttachment->clearStencil);
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	for (auto& c : mColorAttachments)
	{
		glClearColor(c.clearColor.r, c.clearColor.g, c.clearColor.b, c.clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}


std::shared_ptr<ITexture2D>
FramebufferImpl::getDepthStencilAttachment()
{
	if (mDepthStencilAttachment && mDepthStencilAttachment->texture)
	{
		return mDepthStencilAttachment->texture;
	}
	// TODO LOG
	return nullptr;
}


std::shared_ptr<ITexture2D>
FramebufferImpl::getColorAttachment(size_t index)
{
	if (index < mColorAttachments.size() && mColorAttachments[index].texture)
	{
		return mColorAttachments[index].texture;
	}
	// TODO LOG
	return nullptr;
}

} // namespace GL
} // namespace Rendering