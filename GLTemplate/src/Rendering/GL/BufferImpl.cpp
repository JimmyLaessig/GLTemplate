#include "Rendering/GL/BufferImpl.h"

#include "Rendering/GL/ContextImpl.h"

#include "Rendering/Util.h"
#include "Rendering/GL/internal/GLTypes.h"

namespace Rendering
{
namespace GL
{

BufferImpl::BufferImpl(ContextImpl::Ptr ctx) :
	Rendering::IBuffer(ctx)
{}


BufferImpl::~BufferImpl()
{
	glDeleteBuffers(1, &mBufferHandle);
}


std::shared_ptr<BufferImpl>
BufferImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, const IBuffer::Config& config)
{
	if (!context)
	{
		return nullptr;
	}
	
	if (config.data.size() <= 0)
	{
		return nullptr;
	}

	std::shared_ptr<BufferImpl> buffer(new BufferImpl(context));

	buffer->mFormat				= config.format;
	buffer->mBufferType			= config.type;
	buffer->mSize				= config.numElements;

	buffer->createGLBuffer(config.data);

	return buffer;
}


std::shared_ptr<Rendering::GL::ContextImpl>
BufferImpl::getContextImpl()
{
	return std::static_pointer_cast<Rendering::GL::ContextImpl>(getContext());
}


Rendering::AttributeFormat
BufferImpl::getAttributeFormat()  const
{
	return mFormat;
}


size_t
BufferImpl::size() const
{
	return mSize;
}


size_t
BufferImpl::sizeInBytes() const
{
	return mSize * Rendering::sizeInBytes(mFormat);
}


void* 
BufferImpl::getNativeHandle()
{
	return (void*)&mBufferHandle;
}


void 
BufferImpl::createGLBuffer(Base::ByteBufferView data)
{

	// Only use data if the size of the buffer matches the target size
	std::byte* dataPtr = nullptr;
	
	if (sizeInBytes() == data.size())
	{
		dataPtr = data.data();
	}
	else if (data.size() > 0)
	{
		// TODO LOG WARNING BUFFER SIZE MISSMATCH
	}

	GLenum bufferType	= BufferType2GLenum(mBufferType);
	GLenum bufferUsage	= GL_STATIC_DRAW;

	glGenBuffers(1, &mBufferHandle);
	glBindBuffer(bufferType, mBufferHandle);
	glBufferData(bufferType, sizeInBytes(), dataPtr, bufferUsage);
}


GLuint
BufferImpl::getBufferHandle()
{
	return mBufferHandle;
}


bool 
BufferImpl::bind()
{
	GLenum bufferType = BufferType2GLenum(mBufferType);
	glBindBuffer(bufferType, mBufferHandle);

	return true;
}


void
BufferImpl::unbind()
{
	GLenum bufferType = BufferType2GLenum(mBufferType);
	glBindBuffer(bufferType, 0);
}


void 
BufferImpl::setAttributePointer(GLuint index)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index,									// index
						  length(mFormat),							// size
						  DataType2GLenum(getDataType(mFormat)),	// type
						  GL_FALSE,									// normalized
						  0,										// stride
						  0											// pointer
	);
}
}
}