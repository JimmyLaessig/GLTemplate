#pragma once
#include "Rendering/Shader.h"
#include "Rendering/GL/OpenGL.h"

#include <string>
#include <optional>
#include <memory>
#include <vector>


namespace Rendering
{
namespace GL
{
class ContextImpl;
class UniformCollectionImpl;

class GLTEMPLATE_API ShaderProgramImpl : public Rendering::IShaderProgram
{
private:

	ShaderProgramImpl(std::shared_ptr<ContextImpl> ctx);

public:

	using Ptr = std::shared_ptr<ShaderProgramImpl>;


	static ShaderProgramImpl::Ptr create(std::shared_ptr<ContextImpl> context, const IShaderProgram::Config& config);


	std::shared_ptr<Rendering::GL::ContextImpl> getContextImpl();


	~ShaderProgramImpl();


	void* getNativeHandle() override;


	GLuint getProgramHandle();


	bool bind();


	std::shared_ptr<Rendering::IUniformCollection> getGlobalUniformCollection() override;


	const std::vector<AttributeSemantic>& getAttributeSemantics() const override;

private:

	void initializeAttributeSemantics();

	std::vector<AttributeSemantic> mAttributeSemantics;

	GLuint mProgramHandle{0};

	std::vector<GLuint> mShaderHandles;

	std::shared_ptr<UniformCollectionImpl> mGlobalUniforms;



};
}
}