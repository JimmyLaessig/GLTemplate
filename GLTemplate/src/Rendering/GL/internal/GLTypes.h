#pragma once
#include "Base/System.h"

#include "Rendering/Types/DataType.h"
#include "Rendering/Types/AttributeFormat.h"
#include "Rendering/Types/TextureFormat.h"
#include "Rendering/Types/UniformType.h"

#include "Rendering/Buffer.h"

#include "Rendering/PipelineState.h"

#include "Rendering/GL/OpenGL.h"

#include <unordered_map>

namespace Rendering
{

namespace GL
{



constexpr GLenum AttributeFormat2GLenum(const Rendering::AttributeFormat& type)
{
	switch (type)
	{
		case Rendering::AttributeFormat::FLOAT:				return GL_FLOAT;
		case Rendering::AttributeFormat::FLOAT_VEC2:		return GL_FLOAT_VEC2;
		case Rendering::AttributeFormat::FLOAT_VEC3:		return GL_FLOAT_VEC3;
		case Rendering::AttributeFormat::FLOAT_VEC4:		return GL_FLOAT_VEC4;

		case Rendering::AttributeFormat::INT:				return GL_INT;
		case Rendering::AttributeFormat::INT_VEC2:			return GL_INT_VEC2;
		case Rendering::AttributeFormat::INT_VEC3:			return GL_INT_VEC3;
		case Rendering::AttributeFormat::INT_VEC4:			return GL_INT_VEC4;

		case Rendering::AttributeFormat::UNSIGNED_INT:		return GL_UNSIGNED_INT;
		case Rendering::AttributeFormat::UNSIGNED_INT_VEC2:	return GL_UNSIGNED_INT_VEC2;
		case Rendering::AttributeFormat::UNSIGNED_INT_VEC3:	return GL_UNSIGNED_INT_VEC3;
		case Rendering::AttributeFormat::UNSIGNED_INT_VEC4:	return GL_UNSIGNED_INT_VEC4;

		case Rendering::AttributeFormat::DOUBLE:			return GL_DOUBLE;
		case Rendering::AttributeFormat::DOUBLE_VEC2:		return GL_DOUBLE_VEC2;
		case Rendering::AttributeFormat::DOUBLE_VEC3:		return GL_DOUBLE_VEC3;
		case Rendering::AttributeFormat::DOUBLE_VEC4:		return GL_DOUBLE_VEC4;

		case Rendering::AttributeFormat::FLOAT_MATRIX22:	return GL_FLOAT_MAT2;
		case Rendering::AttributeFormat::FLOAT_MATRIX33:	return GL_FLOAT_MAT3;
		case Rendering::AttributeFormat::FLOAT_MATRIX44:	return GL_FLOAT_MAT4;
		case Rendering::AttributeFormat::FLOAT_MATRIX23:	return GL_FLOAT_MAT2x3;
		case Rendering::AttributeFormat::FLOAT_MATRIX24:	return GL_FLOAT_MAT2x4;
		case Rendering::AttributeFormat::FLOAT_MATRIX32:	return GL_FLOAT_MAT3x2;
		case Rendering::AttributeFormat::FLOAT_MATRIX34:	return GL_FLOAT_MAT3x4;
		case Rendering::AttributeFormat::FLOAT_MATRIX42:	return GL_FLOAT_MAT4x2;
		case Rendering::AttributeFormat::FLOAT_MATRIX43:	return GL_FLOAT_MAT4x3;

		case Rendering::AttributeFormat::DOUBLE_MATRIX22:	return GL_DOUBLE_MAT2;
		case Rendering::AttributeFormat::DOUBLE_MATRIX33:	return GL_DOUBLE_MAT3;
		case Rendering::AttributeFormat::DOUBLE_MATRIX44:	return GL_DOUBLE_MAT4;
		case Rendering::AttributeFormat::DOUBLE_MATRIX23:	return GL_DOUBLE_MAT2x3;
		case Rendering::AttributeFormat::DOUBLE_MATRIX24:	return GL_DOUBLE_MAT2x4;
		case Rendering::AttributeFormat::DOUBLE_MATRIX32:	return GL_DOUBLE_MAT3x2;
		case Rendering::AttributeFormat::DOUBLE_MATRIX34:	return GL_DOUBLE_MAT3x4;
		case Rendering::AttributeFormat::DOUBLE_MATRIX42:	return GL_DOUBLE_MAT4x2;
		case Rendering::AttributeFormat::DOUBLE_MATRIX43:	return GL_DOUBLE_MAT4x3;
	};

	assert(false);
	return 0;
}


constexpr Rendering::AttributeFormat GLenum2AttributeFormat(GLenum type)
{
	switch (type)
	{
		case GL_FLOAT:				return Rendering::AttributeFormat::FLOAT;
		case GL_FLOAT_VEC2:			return Rendering::AttributeFormat::FLOAT_VEC2;
		case GL_FLOAT_VEC3:			return Rendering::AttributeFormat::FLOAT_VEC3;
		case GL_FLOAT_VEC4:			return Rendering::AttributeFormat::FLOAT_VEC4;

		case GL_INT:				return Rendering::AttributeFormat::INT;
		case GL_INT_VEC2:			return Rendering::AttributeFormat::INT_VEC2;
		case GL_INT_VEC3:			return Rendering::AttributeFormat::INT_VEC3;
		case GL_INT_VEC4:			return Rendering::AttributeFormat::INT_VEC4;

		case GL_UNSIGNED_INT:		return Rendering::AttributeFormat::UNSIGNED_INT;
		case GL_UNSIGNED_INT_VEC2:	return Rendering::AttributeFormat::UNSIGNED_INT_VEC2;
		case GL_UNSIGNED_INT_VEC3:	return Rendering::AttributeFormat::UNSIGNED_INT_VEC3;
		case GL_UNSIGNED_INT_VEC4:	return Rendering::AttributeFormat::UNSIGNED_INT_VEC4;

		case GL_DOUBLE:				return Rendering::AttributeFormat::DOUBLE;
		case GL_DOUBLE_VEC2:		return Rendering::AttributeFormat::DOUBLE_VEC2;
		case GL_DOUBLE_VEC3:		return Rendering::AttributeFormat::DOUBLE_VEC3;
		case GL_DOUBLE_VEC4:		return Rendering::AttributeFormat::DOUBLE_VEC4;

		case GL_FLOAT_MAT2:			return Rendering::AttributeFormat::FLOAT_MATRIX22;
		case GL_FLOAT_MAT3:			return Rendering::AttributeFormat::FLOAT_MATRIX33;
		case GL_FLOAT_MAT4:			return Rendering::AttributeFormat::FLOAT_MATRIX44;
		case GL_FLOAT_MAT2x3:		return Rendering::AttributeFormat::FLOAT_MATRIX23;
		case GL_FLOAT_MAT2x4:		return Rendering::AttributeFormat::FLOAT_MATRIX24;
		case GL_FLOAT_MAT3x2:		return Rendering::AttributeFormat::FLOAT_MATRIX32;
		case GL_FLOAT_MAT3x4:		return Rendering::AttributeFormat::FLOAT_MATRIX34;
		case GL_FLOAT_MAT4x2:		return Rendering::AttributeFormat::FLOAT_MATRIX42;
		case GL_FLOAT_MAT4x3:		return Rendering::AttributeFormat::FLOAT_MATRIX43;

		case GL_DOUBLE_MAT2:		return Rendering::AttributeFormat::DOUBLE_MATRIX22;
		case GL_DOUBLE_MAT3:		return Rendering::AttributeFormat::DOUBLE_MATRIX33;
		case GL_DOUBLE_MAT4:		return Rendering::AttributeFormat::DOUBLE_MATRIX44;
		case GL_DOUBLE_MAT2x3:		return Rendering::AttributeFormat::DOUBLE_MATRIX23;
		case GL_DOUBLE_MAT2x4:		return Rendering::AttributeFormat::DOUBLE_MATRIX24;
		case GL_DOUBLE_MAT3x2:		return Rendering::AttributeFormat::DOUBLE_MATRIX32;
		case GL_DOUBLE_MAT3x4:		return Rendering::AttributeFormat::DOUBLE_MATRIX34;
		case GL_DOUBLE_MAT4x2:		return Rendering::AttributeFormat::DOUBLE_MATRIX42;
		case GL_DOUBLE_MAT4x3:		return Rendering::AttributeFormat::DOUBLE_MATRIX43;
	};

	assert(false);
	return AttributeFormat{};
}


constexpr GLenum DataType2GLenum(const Rendering::DataType& type)
{
	switch (type)
	{
		case Rendering::DataType::INT8:		return GL_BYTE;
		case Rendering::DataType::UINT8:	return GL_UNSIGNED_BYTE;
		case Rendering::DataType::INT16:	return GL_SHORT;
		case Rendering::DataType::UINT16:	return GL_UNSIGNED_SHORT;
		case Rendering::DataType::INT32:	return GL_INT;
		case Rendering::DataType::UINT32:	return GL_UNSIGNED_INT;
		case Rendering::DataType::FLOAT16:	return GL_HALF_FLOAT;
		case Rendering::DataType::FLOAT32:	return GL_FLOAT;
		case Rendering::DataType::DOUBLE:	return GL_DOUBLE;
	};

	assert(false);
	return 0;
}


constexpr GLenum PrimitiveType2GLenum(Rendering::PrimitiveType dataType)
{
	switch (dataType)
	{
		case Rendering::PrimitiveType::POINTS:			return GL_POINTS;
		case Rendering::PrimitiveType::LINES:			return GL_LINES;
		case Rendering::PrimitiveType::LINE_STRIP:		return GL_LINE_STRIP;
		case Rendering::PrimitiveType::LINE_LOOP:		return GL_LINE_LOOP;
		case Rendering::PrimitiveType::TRIANGLES:		return GL_TRIANGLES;
		case Rendering::PrimitiveType::TRIANGLE_STRIP:	return GL_TRIANGLE_STRIP;
		case Rendering::PrimitiveType::TRIANGLE_FAN:	return GL_TRIANGLE_FAN;
	};

	assert(false);
	return 0;
};


constexpr GLenum BufferType2GLenum(Rendering::BufferType type)
{
	switch (type)
	{
		case BufferType::ATTRIBUTE_BUFFER:	return GL_ARRAY_BUFFER;
		case BufferType::INDEX_BUFFER:		return GL_ELEMENT_ARRAY_BUFFER;
		case BufferType::UNIFORM_BUFFER:	return GL_UNIFORM_BUFFER;
	}
	assert(false);
	return 0;
}


constexpr GLenum BlendFactor2GLenum(Rendering::BlendFactor factor)
{
	switch (factor)
	{
		case BlendFactor::ZERO:						return GL_ZERO;
		case BlendFactor::ONE:						return GL_ONE;
		case BlendFactor::SRC_COLOR:				return GL_SRC_COLOR;
		case BlendFactor::ONE_MINUS_SRC_COLOR:		return GL_ONE_MINUS_SRC_COLOR;
		case BlendFactor::DST_COLOR:				return GL_DST_COLOR;
		case BlendFactor::ONE_MINUS_DST_COLOR:		return GL_ONE_MINUS_DST_COLOR;
		case BlendFactor::SRC_ALPHA:				return GL_SRC_ALPHA;
		case BlendFactor::ONE_MINUS_SRC_ALPHA:		return GL_ONE_MINUS_SRC_ALPHA;
		case BlendFactor::DST_ALPHA:				return GL_DST_ALPHA;
		case BlendFactor::ONE_MINUS_DST_ALPHA:		return GL_ONE_MINUS_DST_ALPHA;
		case BlendFactor::CONSTANT_COLOR:			return GL_CONSTANT_COLOR;
		case BlendFactor::ONE_MINUS_CONSTANT_COLOR:	return GL_ONE_MINUS_CONSTANT_COLOR;
		case BlendFactor::CONSTANT_ALPHA:			return GL_CONSTANT_ALPHA;
		case BlendFactor::ONE_MINUS_CONSTANT_ALPHA:	return GL_ONE_MINUS_CONSTANT_ALPHA;
		case BlendFactor::SRC_ALPHA_SATURATE:		return GL_SRC_ALPHA_SATURATE;
		case BlendFactor::SRC1_COLOR:				return GL_SRC1_COLOR;
		case BlendFactor::ONE_MINUS_SRC1_COLOR:		return GL_ONE_MINUS_SRC1_COLOR;
		case BlendFactor::SRC1_ALPHA:				return GL_SRC1_ALPHA;
		case BlendFactor::ONE_MINUS_SRC1_ALPHA:		return GL_ONE_MINUS_SRC1_ALPHA;
	}

	assert(false);
	return 0;
}


constexpr GLenum BlendFunc2GLenum(Rendering::BlendFunc func)
{
	switch (func)
	{
		case BlendFunc::ADD:				return GL_FUNC_ADD;
		case BlendFunc::SUBTRACT:			return GL_FUNC_SUBTRACT;
		case BlendFunc::REVERSE_SUBTRACT:	return GL_FUNC_REVERSE_SUBTRACT;
		case BlendFunc::MIN:				return GL_MIN;
		case BlendFunc::MAX:				return GL_MAX;
	}
	assert(false);
	return 0;
}


constexpr GLenum DepthFunc2GLenum(Rendering::DepthFunc func)
{
	switch (func)
	{
		case DepthFunc::NEVER:				return GL_NEVER;
		case  DepthFunc::LESS:				return GL_LESS;
		case  DepthFunc::LESS_OR_EQUAL:		return GL_LEQUAL;
		case  DepthFunc::GREATER:			return GL_GREATER;
		case  DepthFunc::GREATER_OR_EQUAL:	return GL_GEQUAL;
		case  DepthFunc::NOT_EQUAL:			return GL_NOTEQUAL;
		case  DepthFunc::ALWAYS:			return GL_ALWAYS;
	}
	assert(false);
	return 0;
}


constexpr GLenum StencilOp2GLenum(Rendering::StencilOp op)
{
	switch (op)
	{
		case StencilOp::KEEP:			return GL_KEEP;
		case StencilOp::ZERO:			return GL_ZERO;
		case StencilOp::REPLACE:		return	GL_REPLACE;
		case StencilOp::INCREMENT:		return GL_INCR;
		case StencilOp::INCREMENT_WRAP: return GL_INCR_WRAP;
		case StencilOp::DECREMENT:		return GL_DECR;
		case StencilOp::DECREMENT_WRAP: return GL_DECR_WRAP;
		case StencilOp::INVERT:			return GL_INVERT;
	}
	assert(false);
	return 0;
}


constexpr GLenum StencilTestFunc2GLenum(StencilTestFunc func)
{
	switch (func)
	{
		case StencilTestFunc::NEVER:			return GL_NEVER;
		case StencilTestFunc::LESS:				return GL_LESS;
		case StencilTestFunc::LESS_OR_EQUAL:	return GL_LEQUAL;
		case StencilTestFunc::GREATER:			return GL_GREATER;
		case StencilTestFunc::GREATER_OR_EQUAL: return GL_GEQUAL;
		case StencilTestFunc::NOT_EQUAL:		return GL_NOTEQUAL;
		case StencilTestFunc::ALWAYS:			return GL_ALWAYS;
	}
	assert(false);
	return 0;
}


constexpr GLenum CullMode2GLenum(Rendering::CullMode mode)
{
	switch (mode)
	{
		case CullMode::FRONT:			return GL_FRONT;
		case CullMode::BACK:			return GL_BACK;
		case CullMode::FRONT_AND_BACK:	return GL_FRONT_AND_BACK;
	}
	assert(false);
	return 0;
}


constexpr GLenum FrontFaceOrientation2GLenum(Rendering::FrontFaceOrientation orientation)
{
	switch (orientation)
	{
		case FrontFaceOrientation::CCW:	return GL_CCW;
		case FrontFaceOrientation::CW:	return GL_CW;
	}
	assert(false);
	return 0;
}


constexpr std::pair<GLenum, GLenum> 
TextureFormat2GLenum(const Rendering::ColorFormat& format)
{
	switch(format)
	{
		case ColorFormat::R8I:		return { GL_RED, GL_RED };
		case ColorFormat::R8UI:		return { GL_RED, GL_RED };
		case ColorFormat::R16I:		return { GL_RED, GL_RED };
		case ColorFormat::R16UI:	return { GL_RED, GL_RED };
		case ColorFormat::R32I:		return { GL_RED, GL_RED };
		case ColorFormat::R32UI:	return { GL_RED, GL_RED };
		case ColorFormat::R16F:		return { GL_RED, GL_RED };
		case ColorFormat::R32F:		return { GL_RED, GL_RED};

		case ColorFormat::RG8I:		return { GL_RG,GL_RG };
		case ColorFormat::RG8UI:	return { GL_RG,GL_RG };
		case ColorFormat::RG16I:	return { GL_RG,GL_RG };
		case ColorFormat::RG16UI:	return { GL_RG,GL_RG };
		case ColorFormat::RG32I:	return { GL_RG,GL_RG };
		case ColorFormat::RG32UI:	return { GL_RG,GL_RG };
		case ColorFormat::RG16F:	return { GL_RG,GL_RG };
		case ColorFormat::RG32F:	return { GL_RG,GL_RG };

		case ColorFormat::RGB8I:	return { GL_RGB, GL_RGB };
		case ColorFormat::RGB8UI:	return { GL_RGB, GL_RGB };
		case ColorFormat::RGB16I:	return { GL_RGB, GL_RGB };
		case ColorFormat::RGB16UI:	return { GL_RGB, GL_RGB };
		case ColorFormat::RGB32I:	return { GL_RGB, GL_RGB };
		case ColorFormat::RGB32UI:	return { GL_RGB, GL_RGB };
		case ColorFormat::RGB16F:	return { GL_RGB, GL_RGB };
		case ColorFormat::RGB32F:	return { GL_RGB, GL_RGB };

		case ColorFormat::RGBA8I:	return { GL_RGBA, GL_RGBA };
		case ColorFormat::RGBA8UI:	return { GL_RGBA, GL_RGBA };
		case ColorFormat::RGBA16I:	return { GL_RGBA, GL_RGBA };
		case ColorFormat::RGBA16UI:	return { GL_RGBA, GL_RGBA };
		case ColorFormat::RGBA32I:	return { GL_RGBA, GL_RGBA };
		case ColorFormat::RGBA32UI:	return { GL_RGBA, GL_RGBA };
		case ColorFormat::RGBA16F:	return { GL_RGBA, GL_RGBA };
		case ColorFormat::RGBA32F:	return { GL_RGBA, GL_RGBA };
	};

	assert(false);
	return {};
}


constexpr std::pair<GLenum, GLenum>
TextureFormat2GLenum(const Rendering::DepthFormat& format)
{
	switch (format)
	{
		case DepthFormat::DEPTH16:			return  { GL_DEPTH_COMPONENT16	, GL_DEPTH_COMPONENT };
		case DepthFormat::DEPTH24:			return  { GL_DEPTH_COMPONENT24	, GL_DEPTH_COMPONENT };
		case DepthFormat::DEPTH32:			return  { GL_DEPTH_COMPONENT32F	, GL_DEPTH_COMPONENT };
		case DepthFormat::DEPTH24STENCIL8:	return  { GL_DEPTH24_STENCIL8	, GL_DEPTH_STENCIL };
	};

	assert(false);
	return {};
}


// Returns the internal format and pixel format for the given texture format
constexpr std::pair<GLenum, GLenum>
TextureFormat2GLenum(const Rendering::TextureFormat& format)
{
	return std::visit([](auto f) {return TextureFormat2GLenum(f); }, format);
}

} // namespace GL
} // namespace Rendering