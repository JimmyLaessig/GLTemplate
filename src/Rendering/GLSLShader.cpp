#include "Rendering/GL/GLSLShader.h"
#include "Rendering/GL/GLSLShaderLoader.h"

#include <iostream>
#include <sstream>



GLSLShader::~GLSLShader()
{
	freeGpuMemory();
}


void GLSLShader::setShaderStageData(const ShaderStageData & shaderStageData)
{
	this->shaderStageData = shaderStageData;
	this->markOutdated();
}


void GLSLShader::freeGpuMemory_Internal()
{
	glDeleteProgram(programHandle);
	glDeleteShader(vertexStage);
	glDeleteShader(geometryStage);
	glDeleteShader(tessellationEvalStage);
	glDeleteShader(tessellationControlStage);
	glDeleteShader(fragmentStage);
	glDeleteShader(computeStage);
}


std::optional<GLuint> GLSLShader::compileShader(const char* shaderCode, GLenum shaderType)
{
	if (strlen(shaderCode) <= 0)
	{
		return {};
	}
	auto handle = glCreateShader(shaderType);
	
	glShaderSource(handle, 1, &shaderCode, NULL);
	glCompileShader(handle);

	std::stringstream ss(shaderCode);
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


void GLSLShader::updateGpuMemory_Internal()
{
	programHandle = glCreateProgram();
	
	vertexStage					= compileShader(shaderStageData.vertexShaderCode.c_str(), GL_VERTEX_SHADER).value_or(0);
	fragmentStage				= compileShader(shaderStageData.fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER).value_or(0);
	geometryStage				= compileShader(shaderStageData.geometryShaderCode.c_str(), GL_GEOMETRY_SHADER).value_or(0);
	tessellationControlStage	= compileShader(shaderStageData.tessellationControlShaderCode.c_str(), GL_TESS_CONTROL_SHADER).value_or(0);
	tessellationEvalStage		= compileShader(shaderStageData.tessellationEvalShaderCode.c_str(), GL_TESS_EVALUATION_SHADER).value_or(0);
	computeStage				= compileShader(shaderStageData.computeShaderCode.c_str(), GL_COMPUTE_SHADER).value_or(0);

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


bool GLSLShader::load()
{
	if (isRuntimeCreated())
		return false;

	setShaderStageData(GLSLShaderLoader::LoadFile(getAssetPath().c_str()));
	return true;
}


bool GLSLShader::reload()
{
	return false;
}

ShaderStageData::ShaderStageData(
	const std::string & vertexShaderCode, 
	const std::string & fragmentShaderCode, 
	const std::string & geometryShaderCode, 
	const std::string & tessellationEvalShaderCode, 
	const std::string & tessellationControlShaderCode, 
	const std::string & computeShaderCode)
	: vertexShaderCode(vertexShaderCode),
	fragmentShaderCode(fragmentShaderCode),
	geometryShaderCode(geometryShaderCode),
	tessellationEvalShaderCode(tessellationEvalShaderCode),
	tessellationControlShaderCode(tessellationControlShaderCode),
	computeShaderCode(computeShaderCode)
{}

ShaderStageData::ShaderStageData(const ShaderStageData & other)
{
	this->vertexShaderCode = other.vertexShaderCode;
	this->fragmentShaderCode = other.fragmentShaderCode;
	this->geometryShaderCode = other.geometryShaderCode;
	this->tessellationControlShaderCode = other.tessellationControlShaderCode;
	this->tessellationEvalShaderCode = other.tessellationEvalShaderCode;
	this->computeShaderCode = other.computeShaderCode;
}

ShaderStageData::ShaderStageData(ShaderStageData && other)
{
	this->vertexShaderCode				= std::move(other.vertexShaderCode);
	this->fragmentShaderCode			= std::move(other.fragmentShaderCode);
	this->geometryShaderCode			= std::move(other.geometryShaderCode);
	this->tessellationControlShaderCode = std::move(other.tessellationControlShaderCode);
	this->tessellationEvalShaderCode	= std::move(other.tessellationEvalShaderCode);
	this->computeShaderCode				= std::move(other.computeShaderCode);
}

ShaderStageData & ShaderStageData::operator=(const ShaderStageData & other)
{
	this->vertexShaderCode				= other.vertexShaderCode;
	this->fragmentShaderCode			= other.fragmentShaderCode;
	this->geometryShaderCode			= other.geometryShaderCode;
	this->tessellationControlShaderCode = other.tessellationControlShaderCode;
	this->tessellationEvalShaderCode	= other.tessellationEvalShaderCode;
	this->computeShaderCode				= other.computeShaderCode;
	return *this;
}

ShaderStageData & ShaderStageData::operator=(ShaderStageData && other)
{
	this->vertexShaderCode = std::move(other.vertexShaderCode);
	this->fragmentShaderCode = std::move(other.fragmentShaderCode);
	this->geometryShaderCode = std::move(other.geometryShaderCode);
	this->tessellationControlShaderCode = std::move(other.tessellationControlShaderCode);
	this->tessellationEvalShaderCode = std::move(other.tessellationEvalShaderCode);
	this->computeShaderCode = std::move(other.computeShaderCode);

	return *this;
}
