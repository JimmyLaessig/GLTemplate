#include "Rendering/GL/Texture2DImpl.h"

#include "Rendering/GL/ContextImpl.h"

#include "Rendering/GL/internal/GLTypes.h"
#include "Rendering/Util.h"

namespace Rendering
{
namespace GL
{

Texture2DImpl::Texture2DImpl(ContextImpl::Ptr ctx) :
	Rendering::ITexture2D(ctx)
{}


Texture2DImpl::~Texture2DImpl()
{
	glDeleteTextures(1, &mNativeHandle);
}


std::shared_ptr<Texture2DImpl>
Texture2DImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, const ITexture2D::Config& config)
{
	if (!context)
	{
		return nullptr;
	}

	if (config.width <= 0 || config.height <= 0)
	{
		return nullptr;
	}
	
	std::shared_ptr<Texture2DImpl> texture(new Texture2DImpl(context));

	texture->mFormat		= config.format;
	texture->mWidth			= config.width;
	texture->mHeight		= config.height;
	texture->mHasMipmaps	= config.generateMipmaps;

	auto [internalFormat, format]	= TextureFormat2GLenum(texture->mFormat);
	auto dataType					= getDataType(texture->mFormat);
	GLenum type						= DataType2GLenum(dataType);

	glGenTextures(1, &texture->mNativeHandle);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->mNativeHandle);

	glTexImage2D(GL_TEXTURE_2D, 
				 0, 
				 internalFormat,
				 texture->mWidth, 
				 texture->mHeight, 
				 0, 
				 format,
				 type,
				 config.data.empty() ? nullptr : config.data.data()
	);

	if (texture->mHasMipmaps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}


std::shared_ptr<Rendering::GL::ContextImpl>
Texture2DImpl::getContextImpl()
{
	return std::static_pointer_cast<Rendering::GL::ContextImpl>(getContext());
}


bool
Texture2DImpl::bind(GLuint location)
{
	glActiveTexture(GL_TEXTURE0 + location);
	glBindTexture(GL_TEXTURE_2D, mNativeHandle);

	return true;
}


void* 
Texture2DImpl::getNativeHandle()
{
	return (void*)&mNativeHandle;
}


GLuint Texture2DImpl::getTextureHandle()
{
	return mNativeHandle;
}

//size_t Texture2DImpl::sizeInBytes() const
//{
//	return mWidth * mHeight;
//}


size_t
Texture2DImpl::getHeight() const
{
	return mHeight;
}


size_t
Texture2DImpl::getWidth() const
{
	return mWidth;
}


bool 
Texture2DImpl::hasMipmaps() const
{
	return mHasMipmaps;
}


TextureFormat
Texture2DImpl::getTextureFormat() const
{
	return mFormat;
}
}
}