#pragma once

#include "Rendering/Texture.h"
#include "Rendering/GL/OpenGL.h"

//#include "Rendering/GL/GLTypes.h"


namespace Rendering
{
namespace GL
{
class ContextImpl;

class Texture2DImpl : public Rendering::ITexture2D
{

private:

	Texture2DImpl(std::shared_ptr<ContextImpl> ctx);

public: 

	using Ptr = std::shared_ptr<Texture2DImpl>;


	~Texture2DImpl();


	static Texture2DImpl::Ptr create(std::shared_ptr<ContextImpl> context, const ITexture2D::Config& config);


	std::shared_ptr<ContextImpl> getContextImpl();


	bool bind(GLuint location);


	void* getNativeHandle() override;


	GLuint getTextureHandle();


	//size_t sizeInBytes() const override;


	/*std::byte* data() override;


	const std::byte* data() const override;*/


	size_t getHeight() const override;


	size_t getWidth() const override;


	bool hasMipmaps() const override;


	TextureFormat getTextureFormat() const override;

private: 
	
	size_t mWidth{0};
	size_t mHeight{0};

	TextureFormat mFormat;
	bool mHasMipmaps{ false };

	GLuint mNativeHandle{ 0 };
};
}
}