#pragma once
#include "Rendering/Shader.h"
#include "Rendering/GL/GLTools.h"
#include <optional>


struct ShaderStageData
{
	ShaderStageData() = default;

	ShaderStageData(
		const std::string& vertexShaderCode,
		const std::string& fragmentShaderCode,
		const std::string& geometryShaderCode,
		const std::string& tessellationEvalShaderCode,
		const std::string& tessellationControlShaderCode,
		const std::string& computeShaderCode);

	ShaderStageData(const ShaderStageData& other);

	ShaderStageData(ShaderStageData&& other);

	ShaderStageData& operator=(const ShaderStageData& other);

	ShaderStageData& operator=(ShaderStageData&& other);

	std::string vertexShaderCode				= "";
	std::string fragmentShaderCode				= "";	
	std::string geometryShaderCode				= "";
	std::string tessellationEvalShaderCode		= "";
	std::string tessellationControlShaderCode	= "";
	std::string computeShaderCode				= "";
};


class GLSLShader : public Shader
{
private: 

	ShaderStageData shaderStageData;

public:

	GLuint programHandle			= 0;
	GLuint vertexStage				= 0;
	GLuint geometryStage			= 0;
	GLuint tessellationEvalStage	= 0;
	GLuint tessellationControlStage = 0;
	GLuint fragmentStage			= 0;
	GLuint computeStage				= 0;

public: 

	virtual ~GLSLShader();


	void setShaderStageData(const ShaderStageData& shaderStageData);


	virtual bool load() override;


	virtual bool reload() override;


	virtual void bind()
	{
		glUseProgram(programHandle);
	}

protected: 

	virtual void freeGpuMemory_Internal() override;


	virtual void updateGpuMemory_Internal() override;

private: 

	static std::optional<GLuint> compileShader(const char* shaderCode, GLenum shaderType);
};

