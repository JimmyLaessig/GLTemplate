#pragma once
#include "Rendering/Shader.h"
#include "Rendering/GL/GLTools.h"
#include <optional>
#include "Rendering/GL/GLTexture2D.h"

template<class UniformType>
constexpr auto getUniformFunction() { UniformType::no_implementation; }

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


template<> constexpr auto getUniformFunction<int>()			{ return glUniform1iv; }
template<> constexpr auto getUniformFunction<glm::ivec2>()	{ return glUniform2iv; }
template<> constexpr auto getUniformFunction<glm::ivec3>()	{ return glUniform3iv; }
template<> constexpr auto getUniformFunction<glm::ivec4>()	{ return glUniform4iv; }
template<> constexpr auto getUniformFunction<unsigned int>(){ return glUniform1uiv; }
template<> constexpr auto getUniformFunction<glm::uvec2>()	{ return glUniform2uiv; }
template<> constexpr auto getUniformFunction<glm::uvec3>()	{ return glUniform3uiv; }
template<> constexpr auto getUniformFunction<glm::uvec4>()	{ return glUniform4uiv; }


//template<> constexpr auto getUniformFunction<const std::vector<float>&>() { return glUniform1fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::vec2>&>() { return glUniform2fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::vec3>&>() { return glUniform3fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::vec4>&>() { return glUniform4fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat2>&>() { return glUniformMatrix2fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat3>&>() { return glUniformMatrix3fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat4>&>() { return glUniformMatrix4fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat2x3>&>() { return glUniformMatrix2x3fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat2x4>&>() { return glUniformMatrix2x4fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat3x2>&>() { return glUniformMatrix3x2fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat3x4>&>() { return glUniformMatrix3x4fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat4x2>&>() { return glUniformMatrix4x2fv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::mat4x3>&>() { return glUniformMatrix4x3fv; }
//
//template<> constexpr auto getUniformFunction<const std::vector<int>&>() { return glUniform1iv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::ivec2>&>() { return glUniform2iv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::ivec3>&>() { return glUniform3iv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::ivec4>&>() { return glUniform4iv; }
//template<> constexpr auto getUniformFunction<const std::vector<unsigned int>&>() { return glUniform1uiv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::uvec2>&>() { return glUniform2uiv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::uvec3>&>() { return glUniform3uiv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::uvec4>&>() { return glUniform4uiv; }
//
//template<> constexpr auto getUniformFunction<const std::vector<double>&>() { return glUniform1dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dvec2>& >() { return glUniform2dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dvec3>& >() { return glUniform3dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dvec4>& >() { return glUniform4dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat2>& >() { return glUniformMatrix2dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat3>& >() { return glUniformMatrix3dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat4>& >() { return glUniformMatrix4dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat2x3>&>() { return glUniformMatrix2x3dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat2x4>&>() { return glUniformMatrix2x4dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat3x2>&>() { return glUniformMatrix3x2dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat3x4>&>() { return glUniformMatrix3x4dv; }
//template<> constexpr auto getUniformFunction<const std::vector<glm::dmat4x3>&>() { return glUniformMatrix4x2dv; }



struct GLSLShaderStageData
{
	GLSLShaderStageData() = default;

	GLSLShaderStageData(
		const std::string& vertexShaderCode,
		const std::string& fragmentShaderCode,
		const std::string& geometryShaderCode,
		const std::string& tessellationEvalShaderCode,
		const std::string& tessellationControlShaderCode,
		const std::string& computeShaderCode);

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


class GLShader : public IShader
{
private: 

	GLSLShaderStageData shaderStageData;

public:

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


	virtual bool load() override;


	virtual bool reload() override;


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

	virtual void freeGpuMemory_Internal() override;


	virtual void updateGpuMemory_Internal() override;

	/**
	 * Binds a single vec2/3/4 to the shader location.
	 */
	template<int C, class T, glm::qualifier Q>
	void bindUniform(int location, const glm::vec<C, T, Q>& value)
	{
		getUniformFunction<glm::vec<C, T, Q>>()(location, 1, glm::value_ptr(value));
	}

	/**
	 * Binds an array of vec<C> to the shader location.
	 */
	template<int C, class T, glm::qualifier Q>
	void bindUniform(int location, const std::initializer_list<glm::vec<C, T, Q>>& value)
	{
		getUniformFunction<glm::vec<C, T, Q>>()(location, (GLsizei)std::size(value), glm::value_ptr(value[0]));
	}

	/**
	 * Binds an array of vec<C> to the shader location.
	 */
	template<int C, class T, glm::qualifier Q>
	void bindUniform(int location, const std::vector<glm::vec<C, T, Q>>& value)
	{
		getUniformFunction<glm::vec<C, T, Q>>()(location, (GLsizei)std::size(value), glm::value_ptr(value[0]));
	}

	/**
	 * Binds a single of mat<CxR> to the shader location.
	 */
	template<int C, int R,  class T, glm::qualifier Q>
	void bindUniform(int location, const glm::mat<C, R, T, Q>& value)
	{
		getUniformFunction<glm::mat<C,R, T, Q>>()(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	/**
	 * Binds an arry of mat<CxR> to the shader location.
	 */
	template<int C, int R, class T, glm::qualifier Q>
	void bindUniform(int location, const std::initializer_list<glm::mat<C, R, T, Q>>& value)
	{
		getUniformFunction<glm::mat<C, R, T, Q>>()(location, (GLsizei)std::size(value), GL_FALSE, glm::value_ptr(value[0]));
	}

	/**
	 * Binds an arry of mat<CxR> to the shader location.
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

	/**
	 * Binds a Texture2D to the shader location.
	 */
	template<class T>
	void bindUniform(int location, const GLTexture2D* texture, int textureUnit)
	{
		glActiveTexture(GLTexture0 + textureUnit);
		glBindTexture(GL_TEXTURE2D, texture ? texture->handle: 0);
		bindUniform(location, GL_TEXTURE0 + textureUnit);
	}

private: 

	static std::optional<GLuint> compileShader(const char* shaderCode, GLenum shaderType);
};

