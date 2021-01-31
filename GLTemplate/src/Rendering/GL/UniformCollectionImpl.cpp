#include "Rendering/GL/UniformCollectionImpl.h"
#include "Rendering/GL/ShaderImpl.h"
#include "Rendering/Types/UniformType.h"

#include "Rendering/GL/ContextImpl.h"

//#include "Rendering/GL/GLTypes.h"
//#include "Rendering/Util.h"

#include <unordered_map>

namespace Rendering
{
namespace GL
{

const std::unordered_map<GLenum, Rendering::UniformType> UNIFORM_TYPE_MAPPING = 
{
	{GL_FLOAT				,UniformType::FLOAT},
	{GL_FLOAT_VEC2			,UniformType::FLOAT_VEC2},
	{GL_FLOAT_VEC3			,UniformType::FLOAT_VEC3},
	{GL_FLOAT_VEC4			,UniformType::FLOAT_VEC4},

	{GL_INT					,UniformType::INT},
	{GL_INT_VEC2			,UniformType::INT_VEC2},
	{GL_INT_VEC3			,UniformType::INT_VEC3},
	{GL_INT_VEC4			,UniformType::INT_VEC4},

	{GL_UNSIGNED_INT		,UniformType::UNSIGNED_INT},
	{GL_UNSIGNED_INT_VEC2	,UniformType::UNSIGNED_INT_VEC2},
	{GL_UNSIGNED_INT_VEC3	,UniformType::UNSIGNED_INT_VEC3},
	{GL_UNSIGNED_INT_VEC4	,UniformType::UNSIGNED_INT_VEC4},

	//{GL_BOOL				,UniformType::BOOL},
	//{GL_BOOL_VEC2			,UniformType::BOOL_VEC2},
	//{GL_BOOL_VEC3			,UniformType::BOOL_VEC3},
	//{GL_BOOL_VEC4			,UniformType::BOOL_VEC4},

	{GL_FLOAT_MAT2			,UniformType::FLOAT_MATRIX22},
	{GL_FLOAT_MAT2x3		,UniformType::FLOAT_MATRIX23},
	{GL_FLOAT_MAT2x4		,UniformType::FLOAT_MATRIX24},

	{GL_FLOAT_MAT3x2		,UniformType::FLOAT_MATRIX32},
	{GL_FLOAT_MAT3			,UniformType::FLOAT_MATRIX33},
	{GL_FLOAT_MAT3x4		,UniformType::FLOAT_MATRIX34},

	{GL_FLOAT_MAT4x2		,UniformType::FLOAT_MATRIX42},
	{GL_FLOAT_MAT4x3		,UniformType::FLOAT_MATRIX43},
	{GL_FLOAT_MAT4			,UniformType::FLOAT_MATRIX44},

	//{GL_DOUBLE			,UniformType::DOUBLE			},
	//{GL_DOUBLE_VEC2		,UniformType::DOUBLE_VEC2		},
	//{GL_DOUBLE_VEC3		,UniformType::DOUBLE_VEC3		},
	//{GL_DOUBLE_VEC4		,UniformType::DOUBLE_VEC4		},
	//{GL_DOUBLE_MAT2		,UniformType::DOUBLE_MATRIX22	},
	//{GL_DOUBLE_MAT2x3		,UniformType::DOUBLE_MATRIX23	},
	//{GL_DOUBLE_MAT2x4		,UniformType::DOUBLE_MATRIX24	},
	//{GL_DOUBLE_MAT3x2		,UniformType::DOUBLE_MATRIX32	},
	//{GL_DOUBLE_MAT3		,UniformType::DOUBLE_MATRIX33	},
	//{GL_DOUBLE_MAT3x4		,UniformType::DOUBLE_MATRIX34	},
	//{GL_DOUBLE_MAT4x2		,UniformType::DOUBLE_MATRIX42	},
	//{GL_DOUBLE_MAT4x3		,UniformType::DOUBLE_MATRIX43	},
	//{GL_DOUBLE_MAT4		,UniformType::DOUBLE_MATRIX44	},
};


template<typename UNIFORM_TYPE>
inline GLenum asGLenum()
{
	static_assert(false);
	return 0;
}

template<> inline GLenum asGLenum<float>()			{ return GL_FLOAT;}
template<> inline GLenum asGLenum<glm::vec2>()		{ return GL_FLOAT_VEC2; }
template<> inline GLenum asGLenum<glm::vec3>()		{ return GL_FLOAT_VEC3; }
template<> inline GLenum asGLenum<glm::vec4>()		{ return GL_FLOAT_VEC4; }

template<> inline GLenum asGLenum<int32_t>()		{ return GL_INT; }
template<> inline GLenum asGLenum<glm::ivec2>()		{ return GL_INT_VEC2; }
template<> inline GLenum asGLenum<glm::ivec3>()		{ return GL_INT_VEC3; }
template<> inline GLenum asGLenum<glm::ivec4>()		{ return GL_INT_VEC4; }

template<> inline GLenum asGLenum<uint32_t>()		{ return GL_UNSIGNED_INT; }
template<> inline GLenum asGLenum<glm::uvec2>()		{ return GL_UNSIGNED_INT_VEC2; }
template<> inline GLenum asGLenum<glm::uvec3>()		{ return GL_UNSIGNED_INT_VEC3; }
template<> inline GLenum asGLenum<glm::uvec4>()		{ return GL_UNSIGNED_INT_VEC4; }

template<> inline GLenum asGLenum<bool>()			{ return GL_BOOL; }
template<> inline GLenum asGLenum<glm::bvec2>()		{ return GL_BOOL_VEC2; }
template<> inline GLenum asGLenum<glm::bvec3>()		{ return GL_BOOL_VEC3; }
template<> inline GLenum asGLenum<glm::bvec4>()		{ return GL_BOOL_VEC4; }

template<> inline GLenum asGLenum<glm::mat2x2>()	{ return GL_FLOAT_MAT2; }
template<> inline GLenum asGLenum<glm::mat2x3>()	{ return GL_FLOAT_MAT2x3; }
template<> inline GLenum asGLenum<glm::mat2x4>()	{ return GL_FLOAT_MAT2x4; }

template<> inline GLenum asGLenum<glm::mat3x2>()	{ return GL_FLOAT_MAT3x2; }
template<> inline GLenum asGLenum<glm::mat3x3>()	{ return GL_FLOAT_MAT3; }
template<> inline GLenum asGLenum<glm::mat3x4>()	{ return GL_FLOAT_MAT3x4; }

template<> inline GLenum asGLenum<glm::mat4x2>()	{ return GL_FLOAT_MAT4x2; }
template<> inline GLenum asGLenum<glm::mat4x3>()	{ return GL_FLOAT_MAT4x3; }
template<> inline GLenum asGLenum<glm::mat4x4>()	{ return GL_FLOAT_MAT4; }


template<typename UNIFORM_TYPE>
inline Rendering::UniformType asUniformValue()
{
	static_assert(false);
	return 0;
}

template<> Rendering::UniformType asUniformValue<float>()		{ return UniformType::FLOAT; }
template<> Rendering::UniformType asUniformValue<glm::vec2>()	{ return UniformType::FLOAT_VEC2; }
template<> Rendering::UniformType asUniformValue<glm::vec3>()	{ return UniformType::FLOAT_VEC3; }
template<> Rendering::UniformType asUniformValue<glm::vec4>()	{ return UniformType::FLOAT_VEC4; }
																		
template<> Rendering::UniformType asUniformValue<int32_t>()		{ return UniformType::INT; }
template<> Rendering::UniformType asUniformValue<glm::ivec2>()	{ return UniformType::INT_VEC2; }
template<> Rendering::UniformType asUniformValue<glm::ivec3>()	{ return UniformType::INT_VEC3; }
template<> Rendering::UniformType asUniformValue<glm::ivec4>()	{ return UniformType::INT_VEC4; }
																		
template<> Rendering::UniformType asUniformValue<uint32_t>()	{ return UniformType::UNSIGNED_INT; }
template<> Rendering::UniformType asUniformValue<glm::uvec2>()	{ return UniformType::UNSIGNED_INT_VEC2; }
template<> Rendering::UniformType asUniformValue<glm::uvec3>()	{ return UniformType::UNSIGNED_INT_VEC3; }
template<> Rendering::UniformType asUniformValue<glm::uvec4>()	{ return UniformType::UNSIGNED_INT_VEC4; }
																
//template<> Rendering::UniformType asUniformValue<bool>()		{ return UniformType::BOOL; }
//template<> Rendering::UniformType asUniformValue<glm::bvec2>()	{ return UniformType::BOOL_VEC2; }
//template<> Rendering::UniformType asUniformValue<glm::bvec3>()	{ return UniformType::BOOL_VEC3; }
//template<> Rendering::UniformType asUniformValue<glm::bvec4>()	{ return UniformType::BOOL_VEC4; }

template<> Rendering::UniformType asUniformValue<glm::mat2x2>() { return UniformType::FLOAT_MATRIX22; }
template<> Rendering::UniformType asUniformValue<glm::mat2x3>() { return UniformType::FLOAT_MATRIX23; }
template<> Rendering::UniformType asUniformValue<glm::mat2x4>() { return UniformType::FLOAT_MATRIX24; }
																		 					  
template<> Rendering::UniformType asUniformValue<glm::mat3x2>() { return UniformType::FLOAT_MATRIX32; }
template<> Rendering::UniformType asUniformValue<glm::mat3x3>() { return UniformType::FLOAT_MATRIX33; }
template<> Rendering::UniformType asUniformValue<glm::mat3x4>() { return UniformType::FLOAT_MATRIX34; }
																							  
template<> Rendering::UniformType asUniformValue<glm::mat4x2>() { return UniformType::FLOAT_MATRIX42; }
template<> Rendering::UniformType asUniformValue<glm::mat4x3>() { return UniformType::FLOAT_MATRIX43; }
template<> Rendering::UniformType asUniformValue<glm::mat4x4>() { return UniformType::FLOAT_MATRIX44; }


UniformCollectionImpl::UniformCollectionImpl(ContextImpl::Ptr ctx) :
	Rendering::IUniformCollection(ctx)
{}


std::shared_ptr<UniformCollectionImpl> 
UniformCollectionImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, std::shared_ptr<Rendering::GL::ShaderProgramImpl> shader)
{
	std::shared_ptr<UniformCollectionImpl> collection(new UniformCollectionImpl(context));

	collection->mShader = shader;
	collection->initializeUniformSignatures();
	return collection;
}


std::shared_ptr<Rendering::GL::ContextImpl>
UniformCollectionImpl::getContextImpl()
{
	return std::static_pointer_cast<Rendering::GL::ContextImpl>(getContext());
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const int value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::ivec2& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::ivec3& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::ivec4& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const uint32_t value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::uvec2& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::uvec3& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::uvec4& value)
{
	return setUniformValueImpl(name, value);
}


bool UniformCollectionImpl::setUniform(std::string_view name, const bool value)		
{
	return setUniformValueImpl(name, value);
}


bool UniformCollectionImpl::setUniform(std::string_view name, const glm::bvec2& value)	
{
	return setUniformValueImpl(name, value);
}


bool UniformCollectionImpl::setUniform(std::string_view name, const glm::bvec3& value)	
{
	return setUniformValueImpl(name, value);
}


bool UniformCollectionImpl::setUniform(std::string_view name, const glm::bvec4& value)	
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const float value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::vec2& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::vec3& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::vec4& value)
{
	return setUniformValueImpl(name, value);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::mat2& matrix)
{
	return setUniformValueImpl(name, matrix);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::mat2x3& matrix)
{
	return setUniformValueImpl(name, matrix);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::mat3x2& matrix)
{
	return setUniformValueImpl(name, matrix);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::mat3& matrix)
{
	return setUniformValueImpl(name, matrix);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::mat3x4& matrix)
{
	return setUniformValueImpl(name, matrix);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::mat4x3& matrix)
{
	return setUniformValueImpl(name, matrix);
}


bool
UniformCollectionImpl::setUniform(std::string_view name, const glm::mat4& matrix)
{
	return setUniformValueImpl(name, matrix);
}


bool 
UniformCollectionImpl::setUniform(std::string_view name, const std::shared_ptr<Rendering::ITexture> texture)
{
	return false;
}


bool
UniformCollectionImpl::bind()
{
	for (auto& [_, value] : mUniformValues)
	{
		switch (value.type)
		{
		case Rendering::UniformType::FLOAT:
			glUniform1fv(value.uniformLocation, 1, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_VEC2:
			glUniform2fv(value.uniformLocation, 1, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_VEC3:
			glUniform3fv(value.uniformLocation, 1, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_VEC4:
			glUniform4fv(value.uniformLocation, 1, (GLfloat*)(value.data.data()));
			break;

		case Rendering::UniformType::INT:
			glUniform1iv(value.uniformLocation, 1, (GLint*)(value.data.data()));
			break;
		case Rendering::UniformType::INT_VEC2:
			glUniform2iv(value.uniformLocation, 1, (GLint*)(value.data.data()));
			break;
		case Rendering::UniformType::INT_VEC3:
			glUniform3iv(value.uniformLocation, 1, (GLint*)(value.data.data()));
			break;
		case Rendering::UniformType::INT_VEC4:
			glUniform4iv(value.uniformLocation, 1, (GLint*)(value.data.data()));
			break;

		case Rendering::UniformType::UNSIGNED_INT:
			glUniform1uiv(value.uniformLocation, 1, (GLuint*)(value.data.data()));
			break;
		case Rendering::UniformType::UNSIGNED_INT_VEC2:
			glUniform1uiv(value.uniformLocation, 1, (GLuint*)(value.data.data()));
			break;
		case Rendering::UniformType::UNSIGNED_INT_VEC3:
			glUniform1uiv(value.uniformLocation, 1, (GLuint*)(value.data.data()));
			break;
		case Rendering::UniformType::UNSIGNED_INT_VEC4:
			glUniform1uiv(value.uniformLocation, 1, (GLuint*)(value.data.data()));
			break;

			/*case Rendering::UniformType::BOOL:
				glUniform1bvoo(value.uniformLocation, 1, (GLuint*)(value.data.data()));
				break;
			case Rendering::UniformType::BOOL_VEC2:
				glUniform1uiv(value.uniformLocation, 1, (GLuint*)(value.data.data()));
				break;
			case Rendering::UniformType::BOOL_VEC3:
				glUniform1uiv(value.uniformLocation, 1, (GLuint*)(value.data.data()));
				break;
			case Rendering::UniformType::BOOL_VEC4:
				glUniform1uiv(value.uniformLocation, 1, (GLuint*)(value.data.data()));
				break;*/

		case Rendering::UniformType::FLOAT_MATRIX22:
			glUniformMatrix2fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX23:
			glUniformMatrix2x3fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX24:
			glUniformMatrix2x4fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX32:
			glUniformMatrix3x2fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX33:
			glUniformMatrix3fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX34:
			glUniformMatrix3x4fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX42:
			glUniformMatrix4x2fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX43:
			glUniformMatrix4x3fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		case Rendering::UniformType::FLOAT_MATRIX44:
			glUniformMatrix4fv(value.uniformLocation, 1, GL_FALSE, (GLfloat*)(value.data.data()));
			break;
		}
	}
	return true;
}


void 
UniformCollectionImpl::initializeUniformSignatures()
{
	mUniformSignatures.clear();

	GLint numUniforms{ 0 };
	GLint bufferSize{ 0 };

	glGetProgramiv(mShader->getProgramHandle(), GL_ACTIVE_UNIFORMS, &numUniforms);
	glGetProgramiv(mShader->getProgramHandle(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufferSize);

	std::vector<char> buffer(bufferSize);

	for (GLuint i = 0; i < numUniforms; ++i)
	{
		GLsizei length{ 0 };
		GLint size{ 0 };
		GLenum type{ 0 };

		glGetActiveUniform(mShader->getProgramHandle(), i, bufferSize, &length, &size, &type, buffer.data());

		std::string name(buffer.data(), length);
		auto uniformType = UNIFORM_TYPE_MAPPING.at(type);

		mUniformSignatures[name] = { i, uniformType };
	}
}


std::optional<std::pair<int, UniformType>> 
UniformCollectionImpl::getUniformSignature(std::string_view name, UniformType type)
{
	std::string s(name.data(), name.size());
	if (mUniformSignatures.count(s) && mUniformSignatures[s].second == type)
	{
		return mUniformSignatures[s];
	}
	return {};
}

} // namespace GL
} // namespace Rendering