#pragma once
#include "Rendering/UniformCollection.h"
#include "Rendering/GL/OpenGL.h"

#include <vector>
#include <map>



namespace Rendering
{
namespace GL
{
	class ContextImpl;
	class ShaderProgramImpl;


	struct UniformValue
	{
		std::string name;
		Rendering::UniformType type{};
		GLuint uniformLocation{ 0 };
		std::vector<std::byte> data;
	};


	struct UniformTexture
	{
		std::string name;
		Rendering::UniformType type{};
		GLuint uniformLocation{ 0 };
		std::shared_ptr<Rendering::ITexture> texture;
	};


class UniformCollectionImpl : public Rendering::IUniformCollection
{

private:

	UniformCollectionImpl(std::shared_ptr<ContextImpl> ctx);

public: 

	using Ptr = std::shared_ptr<UniformCollectionImpl>;


	static UniformCollectionImpl::Ptr create(std::shared_ptr<ContextImpl> context, std::shared_ptr<Rendering::GL::ShaderProgramImpl> shader);


	std::shared_ptr<ContextImpl> getContextImpl();


	bool setUniform(std::string_view name, const int uint32_t)			override;
	bool setUniform(std::string_view name, const glm::ivec2& value)		override;
	bool setUniform(std::string_view name, const glm::ivec3& value)		override;
	bool setUniform(std::string_view name, const glm::ivec4& value)		override;

	bool setUniform(std::string_view name, const uint32_t value)		override;
	bool setUniform(std::string_view name, const glm::uvec2& value)		override;
	bool setUniform(std::string_view name, const glm::uvec3& value)		override;
	bool setUniform(std::string_view name, const glm::uvec4& value)		override;

	bool setUniform(std::string_view name, const bool value)			override;
	bool setUniform(std::string_view name, const glm::bvec2& value)		override;
	bool setUniform(std::string_view name, const glm::bvec3& value)		override;
	bool setUniform(std::string_view name, const glm::bvec4& value)		override;

	bool setUniform(std::string_view name, const float)					override;
	bool setUniform(std::string_view name, const glm::vec2& value)		override;
	bool setUniform(std::string_view name, const glm::vec3& value)		override;
	bool setUniform(std::string_view name, const glm::vec4& value)		override;

	bool setUniform(std::string_view name, const glm::mat2& matrix)		override;
	bool setUniform(std::string_view name, const glm::mat2x3& matrix)	override;
	bool setUniform(std::string_view name, const glm::mat3x2& matrix)	override;
	bool setUniform(std::string_view name, const glm::mat3& matrix)		override;
	bool setUniform(std::string_view name, const glm::mat3x4& matrix)	override;
	bool setUniform(std::string_view name, const glm::mat4x3& matrix)	override;
	bool setUniform(std::string_view name, const glm::mat4& matrix)		override;

	bool setUniform(std::string_view name, const std::shared_ptr <Rendering::ITexture> texture) override;


	bool bind();


	std::shared_ptr<ShaderProgramImpl> getShader()
	{
		return mShader;
	}
	
private:
	using UniformSignature = std::pair<int, UniformType>;

	void initializeUniformSignatures();

	std::optional<UniformSignature> getUniformSignature(std::string_view name, UniformType type);

	std::map<std::string, UniformSignature> mUniformSignatures;


	template< typename Type>
	bool setUniformValueImpl(std::string_view name, const Type& value);


	std::shared_ptr<Rendering::GL::ShaderProgramImpl> mShader;

	std::map<int, UniformValue> mUniformValues;

	std::map<int, UniformTexture> mTextureUniformValues;

};


template<typename Type>
bool 
UniformCollectionImpl::setUniformValueImpl(std::string_view name, const Type& value)
{
	
	/*if (auto signature = getUniformSignature(name, asUniformValue<Type>())
	{
		UniformValue v
		{
			
		};
		mUniformValues.emplace(location, 
								{
									.name = name, 
									.type = type, 
									.uniformLocation = location, 
									.data = std::vector<std::byte>(&value, sizeof(Type))
								});
		return true;
	}*/
	// TODO LOG
	return false;
}

}
}