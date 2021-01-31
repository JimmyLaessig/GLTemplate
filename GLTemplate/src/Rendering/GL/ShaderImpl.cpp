#include "Rendering/GL/ShaderImpl.h"
#include "Rendering/GL/UniformCollectionImpl.h"

#include "Rendering/GL/ContextImpl.h"

#include "Rendering/GL/internal/GLTypes.h"

#include <iostream>

namespace std
{
	template<typename InputType, typename OutputType, typename Functor>
	void transform(const std::optional<InputType>& input , std::optional<OutputType>& output, const Functor& fun)
	{
		if (input)
		{
			output = fun(*input);
		}
		else
		{
			output.reset();
		}
	}
}

namespace Rendering
{
namespace GL
{

ShaderProgramImpl::ShaderProgramImpl(ContextImpl::Ptr ctx) : 
	Rendering::IShaderProgram(ctx)
{}


std::shared_ptr<Rendering::GL::ShaderProgramImpl> 
ShaderProgramImpl::create(std::shared_ptr<Rendering::GL::ContextImpl> context, const IShaderProgram::Config& config)
{

	if (!context)
	{
		return nullptr;
	}
	
	std::shared_ptr<Rendering::GL::ShaderProgramImpl> shader(new Rendering::GL::ShaderProgramImpl(context));

	shader->mProgramHandle = glCreateProgram();


	bool programCompileSuccess = true;


	auto compileShader = [programHandle = shader->mProgramHandle, &handles = shader->mShaderHandles, &success = programCompileSuccess](const std::string& source, GLenum shaderType)
	{
		auto handle = handles.emplace_back(glCreateShader(shaderType));
		auto codePtr = source.c_str();
		// Create the shader and compile it
		glShaderSource(handle, 1, &codePtr, nullptr);
		glCompileShader(handle);

		// Check the shader compile status
		GLint compileStatus;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus);
		auto compileSuccess = compileStatus == GL_TRUE && glIsShader(handle);
		
		// Update the program's compile success
		success &= compileSuccess;

		// Log the error message
		if (compileSuccess)
		{
			glAttachShader(programHandle, handle);
		}
		else
		{
			GLint logSize;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);
			std::string message(logSize, ' ');
			glGetShaderInfoLog(handle, logSize, NULL, message.data());

			std::cout << message << std::endl;
			__debugbreak();
		}
	};

	// Vertex and fragment shader are mandatory
	compileShader(config.vertex, GL_VERTEX_SHADER);
	compileShader(config.fragment, GL_FRAGMENT_SHADER);

	// If set, geometry and tessellation shader are compiled as well
	if (config.geometry)			compileShader(config.geometry.value(), GL_GEOMETRY_SHADER);
	if (config.tessellationControl) compileShader(config.tessellationControl.value(), GL_TESS_CONTROL_SHADER);
	if (config.tessellationEval)	compileShader(config.tessellationEval.value(), GL_TESS_EVALUATION_SHADER);

	// Return if a compilation error occured
	if (!programCompileSuccess)
	{
		return nullptr;
	}

	// Link the shaders to a program
	glLinkProgram(shader->mProgramHandle);

	GLint linkStatus;
	glGetProgramiv(shader->mProgramHandle, GL_LINK_STATUS, &linkStatus);

	
	if (linkStatus == GL_FALSE)
	{
		glLinkProgram(shader->mProgramHandle);

		GLint logSize;
		glGetProgramiv(shader->mProgramHandle, GL_INFO_LOG_LENGTH, &logSize);
		std::string message(logSize, ' ');
		glGetProgramInfoLog(shader->mProgramHandle, logSize, NULL, message.data());

		std::cout << message << std::endl;
		__debugbreak();
		// Return no shader if linking failed
		return nullptr;
	}
	

	// Create the default uniform collection that is bound alongside with the shader
	shader->mGlobalUniforms = std::static_pointer_cast<UniformCollectionImpl>(context->createUniformCollection(shader));

	shader->initializeAttributeSemantics();

	return shader;
}


ShaderProgramImpl::~ShaderProgramImpl()
{
	glDeleteProgram(mProgramHandle);
	for (auto handle : mShaderHandles)
	{
		glDeleteShader(handle);
	}
}


std::shared_ptr<Rendering::GL::ContextImpl>
ShaderProgramImpl::getContextImpl()
{
	return std::static_pointer_cast<Rendering::GL::ContextImpl>(getContext());
}


void* 
ShaderProgramImpl::getNativeHandle()
{
	return &mProgramHandle;
}


GLuint ShaderProgramImpl::getProgramHandle()
{
	return mProgramHandle;
}


bool
ShaderProgramImpl::bind()
{
	glUseProgram(mProgramHandle);
	// Bind the uniforms only once to ensure that shader constants are only bound once and not per draw call
	return mGlobalUniforms->bind();

}


IUniformCollection::Ptr 
ShaderProgramImpl::getGlobalUniformCollection()
{
	return mGlobalUniforms;
}


void 
ShaderProgramImpl::initializeAttributeSemantics()
{
	mAttributeSemantics.clear();

	GLint numAttributes;

	glGetProgramiv(mProgramHandle, GL_ACTIVE_ATTRIBUTES, &numAttributes);

	GLint bufferSize;
	glGetProgramiv(mProgramHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &bufferSize);
	std::vector<char> buffer(bufferSize);

	// Create attribute signatures for each attribute in the shader
	for (GLuint i = 0; i < numAttributes; ++i)
	{
		GLsizei length;
		GLint size;
		GLenum type;

		glGetActiveAttrib(mProgramHandle, i, bufferSize, &length, &size, &type, buffer.data());

		std::string name(buffer.data(), length);
		GLuint location = glGetAttribLocation(mProgramHandle, name.c_str());

		mAttributeSemantics.emplace_back(name, location, GLenum2AttributeFormat(type));
	}
}


const std::vector<AttributeSemantic>&
ShaderProgramImpl::getAttributeSemantics() const
{
	return mAttributeSemantics;
}






}
}