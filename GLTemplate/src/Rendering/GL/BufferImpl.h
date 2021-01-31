#pragma once
#include "Rendering/Buffer.h"
#include "Rendering/GL/OpenGL.h"

namespace Rendering
{
namespace GL
{
class ContextImpl;


class BufferImpl : public Rendering::IBuffer
{

private:

	BufferImpl(std::shared_ptr<ContextImpl> ctx);

public: 
	
	~BufferImpl();


	using Ptr = std::shared_ptr<BufferImpl>;


	static BufferImpl::Ptr create(std::shared_ptr<Rendering::GL::ContextImpl>context, const IBuffer::Config& config);


	size_t size() const;


	size_t sizeInBytes() const;

	
	Rendering::AttributeFormat getAttributeFormat()  const override;


	void* getNativeHandle() override;


	std::shared_ptr<Rendering::GL::ContextImpl> getContextImpl();


	GLuint getBufferHandle();


	bool bind();


	void unbind();


	void setAttributePointer(GLuint location);

private:

	void createGLBuffer(Base::ByteBufferView data);
	

	GLuint mBufferHandle{ 0 };
	
	size_t mSize{ 0 };

	Rendering::AttributeFormat mFormat{ AttributeFormat::FLOAT };

	Rendering::BufferType mBufferType{ BufferType::ATTRIBUTE_BUFFER };
};
}
}