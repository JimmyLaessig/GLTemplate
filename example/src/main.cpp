#include "Base/Enum.h"

#include <iostream>

#include "Application/Application.h"
#include "Application/Window.h"
#include "Rendering/Context.h"
#include "Rendering/Util.h"
#include "Base/PixelFormat.h"
#include "Rendering/Buffer.h"


#include "Rendering/GL/ContextImpl.h"
#include "Rendering/GL/BufferImpl.h"
#include "Rendering/GL/UniformCollectionImpl.h"
#include "Rendering/GL/RenderObjectImpl.h"

#include <array>
#include <span>
#include <variant>
#include <glm/glm.hpp>


int main()
{
	auto app = Application::Application::create(Rendering::GraphicsAPI::OPENGL);
	auto window = app->createWindow({ 1920, 1080 }, "Cool window name", false);

	
	const auto vertexShader =
		R"(
#version 410
layout (location = 0) in vec3 position;


//uniform mat4 modelViewProjectionMatrix;
uniform float scale = 0.5f;
layout (location = 0) out vec2 uv;
void main()
{
	//gl_Position = modelViewProjectionMatrix * vec4(position, 1.0f);
	gl_Position = vec4(position * scale, 1.0f);
	uv = position.xy;
}
)";


	const auto fragmentShader =
		R"(
#version 410
layout (location = 0) in vec2 uv;

//uniform sampler2D tex;

//layout (location = 0) out vec4 fragColor;
void main()
{
	gl_FragColor = vec4(uv * 0.5 + 0.5, 0, 1); //texture(tex, uv) * scale;
}
)";


	/*std::vector<glm::u8vec4> rgb
{
	{255, 255, 0, 255},
};*/

//auto rgbAligned = Rendering::createAlignedBuffer(rgb, 2, 2, mRenderingContext->getTextureRowAlignment());

//Rendering::Texture2DConfig config
//{
//	Rendering::ColorFormat{Rendering::DataType::UINT8, Rendering::Channel::RGB},
//	2,
//	2,
//	std::span(rgbAligned),
//};


//auto texture = ctx->createTexture2D(config);

	std::array<glm::vec3, 4> positions
	{
		glm::vec3{-1.0f, -1.0f, 1.0f},
		glm::vec3{ 1.0f, -1.0f, 1.0f},
		glm::vec3{-1.0f,  1.0f, 1.0f},
		glm::vec3{ 1.0f,  1.0f, 1.0f},
	};

	std::array<uint32_t, 6> indices
	{
		0, 1, 2,
		2, 1, 3
	};
	auto context = window->getContext();

	auto indexConfig = Rendering::makeBufferConfig<uint32_t>(Rendering::BufferType::INDEX_BUFFER, indices);
	auto indexBuffer = context->createBuffer(indexConfig);


	auto posConfig		= Rendering::makeBufferConfig<glm::vec3>(Rendering::BufferType::ATTRIBUTE_BUFFER, positions);
	auto positionBuffer = context->createBuffer(posConfig);


	auto shader = context->createShaderProgram(
	{
		.vertex = vertexShader, 
		.fragment = fragmentShader
	});

	auto uniformCollection = context->createUniformCollection(shader);


	auto pipelineState = context->createPipelineState({});


	uniformCollection->setUniform("scale", 0.5f);
	
	auto mesh = context->createIndexedMesh(
	{
		.primitiveType = Rendering::PrimitiveType::TRIANGLES, 
		.indexBuffer = indexBuffer, 
		.vertexBuffers = {{"position", positionBuffer}}
	});

	auto renderObject = context->createRenderObject(
	{
		.mesh			= mesh,
		.shader			= shader,
		.uniforms		= uniformCollection,
		.pipelineState	= pipelineState
	});
	

	auto renderTask = context->createRenderTask(
	{
			.mRenderObjects = {renderObject},
			.mFrameBuffer = nullptr,
			.mClearOp = Rendering::ClearOp::ON_BIND
	});


	auto depthTexture = context->createTexture2D(
	{
		.format = Rendering::DepthFormat::DEPTH24,
		.width = 1920, 
		.height = 1080, 
	});


	auto colorTexture = context->createTexture2D(
	{
		.format = Rendering::ColorFormat::RGBA8UI,
		.width = 1920,
		.height = 1080,
	});


	auto framebuffer = context->createFramebuffer(
	{ 
		.colorAttachments = {{ colorTexture, {0.0f, 0.0f, 0.0f, 1.0f} }},
		.depthStencilAttachment = {{depthTexture, 1.0f, 0}},
	});


	auto renderTask2 = context->createRenderTask(
	{
			.mRenderObjects = {renderObject},
			.mFrameBuffer = framebuffer,
			.mClearOp = Rendering::ClearOp::ON_BIND
	});

	window->enqueueRenderTask(renderTask);
	window->enqueueRenderTask(renderTask2);

	window->onWindowClosed().subscribe([]{ std::cout << "Tschauseas" << std::endl; });

	app->run();

	return 0;
}