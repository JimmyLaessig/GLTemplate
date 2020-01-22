#include "Rendering/GL/GLShader.h"
#include "Rendering/GL/GLShaderLoader.h"

#include <iostream>
#include <sstream>
#include <Application/Log.h>

GLSLShaderStageData::GLSLShaderStageData(
	std::string_view vertexShaderCode,
	std::string_view fragmentShaderCode,
	std::string_view geometryShaderCode,
	std::string_view tessellationEvalShaderCode,
	std::string_view tessellationControlShaderCode,
	std::string_view computeShaderCode)
	: vertexShaderCode(vertexShaderCode),
	fragmentShaderCode(fragmentShaderCode),
	geometryShaderCode(geometryShaderCode),
	tessellationEvalShaderCode(tessellationEvalShaderCode),
	tessellationControlShaderCode(tessellationControlShaderCode),
	computeShaderCode(computeShaderCode)
{}


GLShader::~GLShader()
{
	freeGpuMemory();
}


void GLShader::setShaderStageData(const GLSLShaderStageData & shaderStageData)
{
	this->shaderStageData = GLSLShaderStageData(shaderStageData);
	this->markOutdated();
}


void GLShader::freeGpuMemory_Internal()
{
	glDeleteProgram(programHandle);
	glDeleteShader(vertexStage);
	glDeleteShader(geometryStage);
	glDeleteShader(tessellationEvalStage);
	glDeleteShader(tessellationControlStage);
	glDeleteShader(fragmentStage);
	glDeleteShader(computeStage);
}





void GLShader::updateGpuMemory_Internal()
{
	programHandle = glCreateProgram();

	vertexStage					= compileGLShaderProgram(shaderStageData.vertexShaderCode.c_str(), GL_VERTEX_SHADER).value_or(0);
	fragmentStage				= compileGLShaderProgram(shaderStageData.fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER).value_or(0);
	geometryStage				= compileGLShaderProgram(shaderStageData.geometryShaderCode.c_str(), GL_GEOMETRY_SHADER).value_or(0);
	tessellationControlStage	= compileGLShaderProgram(shaderStageData.tessellationControlShaderCode.c_str(), GL_TESS_CONTROL_SHADER).value_or(0);
	tessellationEvalStage		= compileGLShaderProgram(shaderStageData.tessellationEvalShaderCode.c_str(), GL_TESS_EVALUATION_SHADER).value_or(0);
	computeStage				= compileGLShaderProgram(shaderStageData.computeShaderCode.c_str(), GL_COMPUTE_SHADER).value_or(0);

	if (vertexStage)				glAttachShader(programHandle, vertexStage);
	if (fragmentStage)				glAttachShader(programHandle, fragmentStage);
	if (geometryStage)				glAttachShader(programHandle, geometryStage);
	if (tessellationControlStage)	glAttachShader(programHandle, tessellationControlStage);
	if (tessellationEvalStage)		glAttachShader(programHandle, tessellationEvalStage);
	if (computeStage)				glAttachShader(programHandle, computeStage);

	glLinkProgram(programHandle);

	GLint succeded;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &succeded);

	if (!succeded)
	{
		GLint logSize;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logSize);
		std::string msg(logSize, ' ');
		glGetProgramInfoLog(programHandle, logSize, NULL, msg.data());

		std::cerr << "Failed to link Shader Program: " << msg.c_str() << std::endl;
		freeGpuMemory_Internal();
	}
}


//bool GLShader::load()
//{
//	if (isRuntimeCreated())
//		return false;
//
//	setShaderStageData(GLShaderLoader::LoadFile(getAssetPath().c_str()));
//	return true;
//}
//
//
//bool GLShader::reload()
//{
//	return false;
//}







//template<> void GLShader::bindUniform(int location, float value)				{ glUniform1f(			location, value);}
//template<> void GLShader::bindUniform(int location, const glm::vec2& value)		{ glUniform2f(			location, value.x, value.y);}
//template<> void GLShader::bindUniform(int location, const glm::vec3& value)		{ glUniform3f(			location, value.x, value.y, value.z);};
//template<> void GLShader::bindUniform(int location, const glm::vec4& value)		{ glUniform4f(			location, value.x, value.y, value.z, value.a );}
//template<> void GLShader::bindUniform(int location, const glm::mat2& value)		{ glUniformMatrix2fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//template<> void GLShader::bindUniform(int location, const glm::mat3& value)		{ glUniformMatrix3fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//template<> void GLShader::bindUniform(int location, const glm::mat4& value)		{ glUniformMatrix4fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//template<> void GLShader::bindUniform(int location, const glm::mat2x3& value)	{ glUniformMatrix2x3fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//template<> void GLShader::bindUniform(int location, const glm::mat2x4& value)	{ glUniformMatrix2x4fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//template<> void GLShader::bindUniform(int location, const glm::mat3x2& value)	{ glUniformMatrix3x2fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//template<> void GLShader::bindUniform(int location, const glm::mat3x4& value)	{ glUniformMatrix3x4fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//template<> void GLShader::bindUniform(int location, const glm::mat4x2& value)	{ glUniformMatrix4x2fv( location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::mat4x3& value)	{ glUniformMatrix4x3fv(	location, 1, GL_FALSE, glm::value_ptr(value));}
//
//template<> void GLShader::bindUniform(int location, double value)				{ glUniform1d(			location, value); }
//template<> void GLShader::bindUniform(int location, const glm::dvec2& value)	{ glUniform2d(			location, value.x, value.y); }
//template<> void GLShader::bindUniform(int location, const glm::dvec3& value)	{ glUniform3d(			location, value.x, value.y, value.z); };
//template<> void GLShader::bindUniform(int location, const glm::dvec4& value)	{ glUniform4d(			location, value.x, value.y, value.z, value.a); }
//template<> void GLShader::bindUniform(int location, const glm::dmat2& value)	{ glUniformMatrix2dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat3& value)	{ glUniformMatrix3dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat4& value)	{ glUniformMatrix4dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat2x3& value)	{ glUniformMatrix2x3dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat2x4& value)	{ glUniformMatrix2x4dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat3x2& value)	{ glUniformMatrix3x2dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat3x4& value)	{ glUniformMatrix3x4dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat4x2& value)	{ glUniformMatrix4x2dv( location, 1, GL_FALSE, glm::value_ptr(value)); }
//template<> void GLShader::bindUniform(int location, const glm::dmat4x3& value)	{ glUniformMatrix4x3dv(	location, 1, GL_FALSE, glm::value_ptr(value)); }
//
//template<> void GLShader::bindUniform(int location, int& value)			{ glUniform1i(	location, value); }
//template<> void GLShader::bindUniform(int location, glm::ivec2& value)	{ glUniform2i(	location, value.x, value.y); }
//template<> void GLShader::bindUniform(int location, glm::ivec3& value)	{ glUniform3i(	location, value.x, value.y, value.z); }
//template<> void GLShader::bindUniform(int location, glm::ivec4& value)	{ glUniform4i(	location, value.x, value.y, value.z, value.a); }
//template<> void GLShader::bindUniform(int location, unsigned int value)	{ glUniform1ui(	location, value); }
//template<> void GLShader::bindUniform(int location, glm::uvec2& value)	{ glUniform2ui(	location, value.x, value.y); }
//template<> void GLShader::bindUniform(int location, glm::uvec3& value)	{ glUniform3ui(	location, value.x, value.y, value.z); };
//template<> void GLShader::bindUniform(int location, glm::uvec4& value)	{ glUniform4ui(	location, value.x, value.y, value.z, value.a); }
//	
//
//template<>void GLShader::bindUniform(int location, const std::vector<float>& values)		{ glUniform1fv(			location, (GLsizei)values.size(),			values.data()); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::vec2>& values)	{ glUniform2fv(			location, (GLsizei)values.size(),			glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::vec3>& values)	{ glUniform3fv(			location, (GLsizei)values.size(),			glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::vec4>& values)	{ glUniform4fv(			location, (GLsizei)values.size(),			glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat2>& values)	{ glUniformMatrix2fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat3>& values)	{ glUniformMatrix3fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat4>& values)	{ glUniformMatrix4fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat2x3>& values)	{ glUniformMatrix2x3fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat2x4>& values)	{ glUniformMatrix2x4fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat3x2>& values)	{ glUniformMatrix3x2fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat3x4>& values)	{ glUniformMatrix3x4fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::mat4x3>& values)	{ glUniformMatrix4x2fv(	location, (GLsizei)values.size(), GL_FALSE,	glm::value_ptr(values[0])); }
//
//template<>void GLShader::bindUniform(int location, const std::vector<int>& values)			{ glUniform1iv(location, (GLsizei)values.size(), values.data());}
//template<>void GLShader::bindUniform(int location, const std::vector<glm::ivec2>& values)	{ glUniform2iv(location, (GLsizei)values.size(), glm::value_ptr(values[0]));}
//template<>void GLShader::bindUniform(int location, const std::vector<glm::ivec3>& values)	{ glUniform3iv(location, (GLsizei)values.size(), glm::value_ptr(values[0]));}
//template<>void GLShader::bindUniform(int location, const std::vector<glm::ivec4>& values)	{ glUniform4iv(location, (GLsizei)values.size(), glm::value_ptr(values[0]));}
//template<>void GLShader::bindUniform(int location, const std::vector<unsigned int>& values) { glUniform1uiv(location, (GLsizei)values.size(), values.data()); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::uvec2>& values)	{ glUniform2uiv(location, (GLsizei)values.size(), glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::uvec3>& values)	{ glUniform3uiv(location, (GLsizei)values.size(), glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::uvec4>& values)	{ glUniform4uiv(location, (GLsizei)values.size(), glm::value_ptr(values[0])); }
//
//template<>void GLShader::bindUniform(int location, const std::vector<double>& values)		{ glUniform1dv(location, (GLsizei)values.size(), values.data()); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dvec2>& values)	{ glUniform2dv(location, (GLsizei)values.size(), glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dvec3>& values)	{ glUniform3dv(location, (GLsizei)values.size(), glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dvec4>& values)	{ glUniform4dv(location, (GLsizei)values.size(), glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat2>& values)	{ glUniformMatrix2dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat3>& values)	{ glUniformMatrix3dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat4>& values)	{ glUniformMatrix4dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat2x3>& values) { glUniformMatrix2x3dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat2x4>& values) { glUniformMatrix2x4dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat3x2>& values) { glUniformMatrix3x2dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat3x4>& values) { glUniformMatrix3x4dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }
//template<>void GLShader::bindUniform(int location, const std::vector<glm::dmat4x3>& values) { glUniformMatrix4x2dv(location, (GLsizei)values.size(), GL_FALSE, glm::value_ptr(values[0])); }



//
//
//
//

std::optional<GLuint> compileGLShaderProgram(std::string_view shaderCode, GLenum shaderType)
{
	if (shaderCode.size() <= 0)
	{
		return {};
	}
	auto handle = glCreateShader(shaderType);
	auto codePtr = shaderCode.data();
	glShaderSource(handle, 1, &codePtr, NULL);
	glCompileShader(handle);

	std::stringstream ss(shaderCode.data());
	int lineNumber = 1;
	std::cout << "Compiling Shader: " << std::endl;
	for (std::string line; std::getline(ss, line); lineNumber++)
	{
		std::cout << lineNumber++ << +":\t" << line << std::endl;
	}

	GLint succeded;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &succeded);
	if (succeded == GL_FALSE || !glIsShader(handle))
	{
		GLint logSize;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);

		std::string log(logSize, ' ');
		glGetShaderInfoLog(handle, logSize, NULL, log.data());
		std::cerr << "Failed to compile Shader: " << log.c_str() << std::endl;

		glDeleteShader(handle);
		return {};
	}

	return handle;
}