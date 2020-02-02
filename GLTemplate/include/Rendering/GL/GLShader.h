#pragma once
#include <optional>

#include "Rendering/GL/GL.h"
#include "Rendering/GL/GLTexture2D.h"

#include "Rendering/GpuShader.h"


/**
 * Templated function that returns the proper glUniform function for the UniformType. 
 * For sake of sanity, glUniform1/2/3/4* returns the vectorized version of the function.
 * E.g.: getUniformFunction<float>() returns glUniform1fv. So the function arguments are consitent for all vector types and matrix types.
 * Let T be the data type of the elements of the matrices/vector (e.g. float for vec3):
 * 
 * The function signature for all scalar and vector types: 
 *		void(GLuint location, GLuint count, T* data) 
 * The function signature for all matrix types: 
 *		void(GLuint location, GLuint count, GLbool transpose, T* data) 
 */
template<class UniformType>
constexpr auto getUniformFunction() { UniformType::no_implementation; }

// Float
template<> constexpr auto getUniformFunction<float>()		{ return glUniform1fv; }
template<> constexpr auto getUniformFunction<glm::vec2>()	{ return glUniform2fv; }
template<> constexpr auto getUniformFunction<glm::vec3>()	{ return glUniform3fv; }
template<> constexpr auto getUniformFunction<glm::vec4>()	{ return glUniform4fv; }
template<> constexpr auto getUniformFunction<glm::mat2>()	{ return glUniformMatrix2fv; }
template<> constexpr auto getUniformFunction<glm::mat3>()	{ return glUniformMatrix3fv; }
template<> constexpr auto getUniformFunction<glm::mat4>()	{ return glUniformMatrix4fv; }
template<> constexpr auto getUniformFunction<glm::mat2x3>() { return glUniformMatrix2x3fv; }
template<> constexpr auto getUniformFunction<glm::mat2x4>() { return glUniformMatrix2x4fv; }
template<> constexpr auto getUniformFunction<glm::mat3x2>() { return glUniformMatrix3x2fv; }
template<> constexpr auto getUniformFunction<glm::mat3x4>() { return glUniformMatrix3x4fv; }
template<> constexpr auto getUniformFunction<glm::mat4x2>() { return glUniformMatrix4x2fv; }
template<> constexpr auto getUniformFunction<glm::mat4x3>() { return glUniformMatrix4x3fv; }
// Double
template<> constexpr auto getUniformFunction<double>()		{ return glUniform1dv; }
template<> constexpr auto getUniformFunction<glm::dvec2>()	{ return glUniform2dv; }
template<> constexpr auto getUniformFunction<glm::dvec3>()	{ return glUniform3dv; }
template<> constexpr auto getUniformFunction<glm::dvec4>()	{ return glUniform4dv; }
template<> constexpr auto getUniformFunction<glm::dmat2>()	{ return glUniformMatrix2dv; }
template<> constexpr auto getUniformFunction<glm::dmat3>()	{ return glUniformMatrix3dv; }
template<> constexpr auto getUniformFunction<glm::dmat4>()	{ return glUniformMatrix4dv; }
template<> constexpr auto getUniformFunction<glm::dmat2x3>(){ return glUniformMatrix2x3dv; }
template<> constexpr auto getUniformFunction<glm::dmat2x4>(){ return glUniformMatrix2x4dv; }
template<> constexpr auto getUniformFunction<glm::dmat3x2>(){ return glUniformMatrix3x2dv; }
template<> constexpr auto getUniformFunction<glm::dmat3x4>(){ return glUniformMatrix3x4dv; }
template<> constexpr auto getUniformFunction<glm::dmat4x2>(){ return glUniformMatrix4x2dv; }
template<> constexpr auto getUniformFunction<glm::dmat4x3>(){ return glUniformMatrix4x3dv; }
// Int
template<> constexpr auto getUniformFunction<int>()			{ return glUniform1iv; }
template<> constexpr auto getUniformFunction<glm::ivec2>()	{ return glUniform2iv; }
template<> constexpr auto getUniformFunction<glm::ivec3>()	{ return glUniform3iv; }
template<> constexpr auto getUniformFunction<glm::ivec4>()	{ return glUniform4iv; }
// Unsigned Int
template<> constexpr auto getUniformFunction<uint32_t>()	{ return glUniform1uiv; }
template<> constexpr auto getUniformFunction<glm::uvec2>()	{ return glUniform2uiv; }
template<> constexpr auto getUniformFunction<glm::uvec3>()	{ return glUniform3uiv; }
template<> constexpr auto getUniformFunction<glm::uvec4>()	{ return glUniform4uiv; }


struct GLSLShaderStageData
{
	GLSLShaderStageData() = default;
	
	GLSLShaderStageData(
		std::string_view vertexShaderCode,
		std::string_view fragmentShaderCode,
		std::string_view geometryShaderCode,
		std::string_view tessellationEvalShaderCode,
		std::string_view tessellationControlShaderCode,
		std::string_view computeShaderCode);

	GLSLShaderStageData(const GLSLShaderStageData& other) = default;

	GLSLShaderStageData(GLSLShaderStageData&& other) = default;

	GLSLShaderStageData& operator=(const GLSLShaderStageData& other) = default;

	std::string vertexShaderCode				= "";
	std::string fragmentShaderCode				= "";	
	std::string geometryShaderCode				= "";
	std::string tessellationEvalShaderCode		= "";
	std::string tessellationControlShaderCode	= "";
	std::string computeShaderCode				= "";
};


class GLShader : public IBackendShader
{
private: 

	GLSLShaderStageData shaderStageData;

public:

	GLShader(const Shader* shader) :
		IBackendShader(shader)
	{
		markOutdated();
	}


	GLuint programHandle			= 0;
	GLuint vertexStage				= 0;
	GLuint geometryStage			= 0;
	GLuint tessellationEvalStage	= 0;
	GLuint tessellationControlStage = 0;
	GLuint fragmentStage			= 0;
	GLuint computeStage				= 0;

public: 

	virtual ~GLShader();


	void setShaderStageData(const GLSLShaderStageData& shaderStageData);


	virtual void bind()
	{
		glUseProgram(programHandle);
		bindUniform(1, glm::vec3());
		bindUniform(1, 1);
		bindUniform(1, 1.0f);
		bindUniform(1, 1.0);
		bindUniform(1, glm::mat4(1));
		bindUniform(1, std::vector<glm::mat4>{glm::mat4(1), glm::mat4(1)});	
	}

protected: 

	virtual void freeGpuMemoryImpl() override;


	virtual void updateGpuMemoryImpl() override;

	/**
	 * Binds a single vec2/3/4 to the shader location.
	 */
	template<int C, class T, glm::qualifier Q>
	void bindUniform(int location, const glm::vec<C, T, Q>& value)
	{
		getUniformFunction<glm::vec<C, T, Q>>()(location, 1, glm::value_ptr(value));
	}

	/**
	 * Binds an array of glm::vec<C> to the shader location.
	 */
	template<int C, class T, glm::qualifier Q>
	void bindUniform(int location, const std::initializer_list<glm::vec<C, T, Q>>& value)
	{
		getUniformFunction<glm::vec<C, T, Q>>()(location, (GLsizei)std::size(value), glm::value_ptr(value[0]));
	}

	/**
	 * Binds an array of glm::vec<C> to the shader location.
	 */
	template<int C, class T, glm::qualifier Q>
	void bindUniform(int location, const std::vector<glm::vec<C, T, Q>>& value)
	{
		getUniformFunction<glm::vec<C, T, Q>>()(location, (GLsizei)std::size(value), glm::value_ptr(value[0]));
	}

	/**
	 * Binds a single of glm::mat<CxR> to the shader location.
	 */
	template<int C, int R,  class T, glm::qualifier Q>
	void bindUniform(int location, const glm::mat<C, R, T, Q>& value)
	{
		getUniformFunction<glm::mat<C,R, T, Q>>()(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	/**
	 * Binds an arry of glm::mat<CxR> to the shader location.
	 */
	template<int C, int R, class T, glm::qualifier Q>
	void bindUniform(int location, const std::initializer_list<glm::mat<C, R, T, Q>>& value)
	{
		getUniformFunction<glm::mat<C, R, T, Q>>()(location, (GLsizei)std::size(value), GL_FALSE, glm::value_ptr(value[0]));
	}

	/**
	 * Binds an arry of glm::mat<CxR> to the shader location.
	 */
	template<int C, int R, class T, glm::qualifier Q>
	void bindUniform(int location, const std::vector<glm::mat<C, R, T, Q>>& value)
	{
		getUniformFunction<glm::mat<C, R, T, Q>>()(location, (GLsizei)std::size(value), GL_FALSE, glm::value_ptr(value[0]));
	}

	/**
	 * Binds an int/uint/float/double value to the shader location.
	 */
	template<class T>
	void bindUniform(int location, T value)
	{
		getUniformFunction<T>()(location, 1, &value);
	}

	/**
	 * Binds an array of int/uint/float/double values to the shader location.
	 */
	template<class T>
	void bindUniform(int location, const std::initializer_list<T>& values)
	{
		getUniformFunction<T>()(location, (GLsizei)std::size(values), values.data());
	}

	/**
	 * Binds an array of int/uint/float/double values to the shader location.
	 */
	template<class T>
	void bindUniform(int location, const std::vector<T>& values)
	{
		getUniformFunction<T>()(location, (GLsizei)std::size(values), values.data());
	}

	//template <class T>
	//void binUniformBuffer(int location, const T& buffer)
	//{
	//	//glUniformBufferEXT(this->programHandle, location, );
	//}


	/**
	 * Binds a Texture2D to the shader location.
	 */
	void bindUniform(int location, const GLTexture2D* texture, int textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, texture ? texture->handle: 0);
		bindUniform(location, GL_TEXTURE0 + textureUnit);
	}
};


std::optional<GLuint> compileGLShaderProgram(std::string_view shaderCode, GLenum shaderType);