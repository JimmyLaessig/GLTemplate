#pragma once
#include "GpuResource.h"
#include "SharedAsset.h"
#include "GL/glew.h"
#include <optional>


struct ShaderStageData
{
	std::string vertexShaderCode				= "";
	std::string fragmentShaderCode				= "";	
	std::string geometryShaderCode				= "";
	std::string tessellationEvalShaderCode		= "";
	std::string tessellationControlShaderCode	= "";
	std::string computeShaderCode				= "";
};



class GLSLShader : public GpuResource, public SharedAsset
{
private: 


	ShaderStageData shaderStageData;

	GLuint programHandle			= 0;
	GLuint vertexStage				= 0;
	GLuint geometryStage			= 0;
	GLuint tessellationEvalStage	= 0;
	GLuint tessellationControlStage = 0;
	GLuint fragmentStage			= 0;
	GLuint computeStage				= 0;

public: 

	//GLSLShader() = default;

	virtual ~GLSLShader();


	void setShaderStageData(const ShaderStageData& shaderStageData);


	virtual bool load() override;


	virtual bool reload() override;


protected: 

	virtual void freeGpuMemory_Internal() override;


	virtual void updateGpuMemory_Internal() override;

private: 

	static std::optional<GLuint> compileShader(const char* shaderCode, GLenum shaderType);
};


class GLSLShaderAlt : public GpuResource, public SharedAsset
{
private:


	ShaderStageData shaderStageData;

	GLuint programHandle = 0;
	GLuint vertexStage = 0;
	GLuint geometryStage = 0;
	GLuint tessellationEvalStage = 0;
	GLuint tessellationControlStage = 0;
	GLuint fragmentStage = 0;
	GLuint computeStage = 0;

public:

	//GLSLShader() = default;

	virtual ~GLSLShaderAlt() {}


	void setShaderStageData(const ShaderStageData& shaderStageData) {}


	virtual bool load() override { return false; }


	virtual bool reload() override { return false; }


protected:

	virtual void freeGpuMemory_Internal() override {}


	virtual void updateGpuMemory_Internal() override {}


};

