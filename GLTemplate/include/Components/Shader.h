
#pragma once

#include "SharedAsset.h"
#include "VectorMath.h"
#include <variant>
#include "Rendering/GpuShader.h"


//enum class ShadingStage
//{
//	VERTEX,
//	TESSELATION_CONTROL,
//	TESSELLATION_EVALUATION,
//	GEOMETRY,
//
//};

class Shader : public SharedAsset
{
public:
	
	Shader();


	template<class T>
	void setUniform(const std::string& name, T value)
	{
		uniformCollections[name] = value;
	};


	typedef std::variant<
		float, glm::vec2, glm::vec3, glm::vec4, glm::mat2, glm::mat3, glm::mat4, glm::mat2x3, glm::mat2x4, glm::mat3x2, glm::mat3x4, glm::mat4x3,
		int, glm::ivec2, glm::ivec3, glm::ivec4, unsigned int, glm::uvec2, glm::uvec3, glm::uvec4,
		double, glm::dvec2, glm::dvec3, glm::dvec4, glm::dmat2, glm::dmat3, glm::dmat4, glm::dmat2x3, glm::dmat2x4, glm::dmat3x2, glm::dmat3x4, glm::dmat4x3
		> UniformVariant;


	void setShaderCode(const std::string_view code)
	{
		this->sourceCode = code;
	}


	const std::string& getShaderCode() const
	{
		return this->sourceCode;
	}

protected:


	std::string sourceCode;


	std::map<std::string, UniformVariant> uniformCollections;


private: 

	std::unique_ptr<IBackendShader> backendShader;
};



class ShaderLoader
{
public: 
	static bool Load(Shader* shader, const std::string_view path);
};
