#pragma once
#include "Rendering/internal/BaseObject.h"

#include "Rendering/Types/UniformType.h"

#include <glm/glm.hpp>
#include <string_view>


namespace Rendering
{
class ITexture;

class GLTEMPLATE_API IUniformCollection : public Rendering::BaseObject
{
public:
	using Rendering::BaseObject::BaseObject;

	using Ptr = std::shared_ptr<IUniformCollection>;

	//virtual UniformType getUniformType(std::string_view name) = 0;


	//virtual UniformType getUniformType(uint32_t location) = 0;


	//virtual std::vector<std::string> getUniformNames() = 0;


	/*virtual std::vector<UniformSignature> getUniformSignatures() = 0;

	virtual std::vector<UniformSignature> getUniformBlockSignature(std::string_view name) = 0;

	virtual std::vector<UniformBlockSignature> getUniformBlockSignatures() = 0;*/


	//virtual bool hasUniform(std::string_view name) = 0;

	//virtual bool hasUniform(std::string_view name, UniformType type) = 0;


	virtual bool setUniform(std::string_view name, const int uint32_t)			= 0;
	virtual bool setUniform(std::string_view name, const glm::ivec2& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::ivec3& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::ivec4& value)		= 0;

	virtual bool setUniform(std::string_view name, const uint32_t value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::uvec2& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::uvec3& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::uvec4& value)		= 0;

	virtual bool setUniform(std::string_view name, const float)					= 0;
	virtual bool setUniform(std::string_view name, const glm::vec2& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::vec3& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::vec4& value)		= 0;

	virtual bool setUniform(std::string_view name, const bool value)			= 0;
	virtual bool setUniform(std::string_view name, const glm::bvec2& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::bvec3& value)		= 0;
	virtual bool setUniform(std::string_view name, const glm::bvec4& value)		= 0;

	virtual bool setUniform(std::string_view name, const glm::mat2& matrix)		= 0;
	virtual bool setUniform(std::string_view name, const glm::mat2x3& matrix)	= 0;
	virtual bool setUniform(std::string_view name, const glm::mat3x2& matrix)	= 0;
	virtual bool setUniform(std::string_view name, const glm::mat3& matrix)		= 0;
	virtual bool setUniform(std::string_view name, const glm::mat3x4& matrix)	= 0;
	virtual bool setUniform(std::string_view name, const glm::mat4x3& matrix)	= 0;
	virtual bool setUniform(std::string_view name, const glm::mat4& matrix)		= 0;

	virtual bool setUniform(std::string_view name, const std::shared_ptr <Rendering::ITexture> texture) = 0;
	//virtual bool setUniform(std::string_view name, const std::span<uint32_t> values)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::ivec2> values)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::ivec3> values)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::ivec4> values)	= 0;
	//									
	//virtual bool setUniform(std::string_view name, const std::span<uint32_t> values)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::uvec2> values)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::uvec3> values)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::uvec4> values)	= 0;
	//										
	//virtual bool setUniform(std::string_view name, const std::span<float>  value)		= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::vec2> value)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::vec3> value)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::vec4> value)	= 0;
	//										
	//virtual bool setUniform(std::string_view name, const std::span<glm::mat2> matrices)		= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::mat2x3> matrices)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::mat3x2> matrices)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::mat3> matrices)		= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::mat3x4> matrices)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::mat4x3> matrices)	= 0;
	//virtual bool setUniform(std::string_view name, const std::span<glm::mat4> matrices)		= 0;


	//virtual bool setUniformBlock(std::string_view name, std::span<std::byte> data) = 0;
};

} // namespace Rendering
