//#include <catch2/catch.hpp>
//#include "Application/Delegates.h"
//#include "Rendering/GL/GLTypeConversion.h"
//#include "Rendering/GL/GLResourceBackend.h"
//#include "Application/GL/GLWindow.h"
//#include "Components/Texture2D.h"
//#include "Rendering/GL/GLTexture2D.h"
//
//
//#include "GLFW/glfw3.h"
//
//using namespace GLTypeConversion;
//
//template<typename T,glm::qualifier Q>
//void toGLPixelFormatTestGLM()
//{
//	CHECK(toGLPixelFormat<glm::vec<1, T, Q>>() == GL_RED);
//	CHECK(toGLPixelFormat<glm::vec<2, T, Q>>() == GL_RG);
//	CHECK(toGLPixelFormat<glm::vec<3, T, Q>>() == GL_RGB);
//	CHECK(toGLPixelFormat<glm::vec<4, T, Q>>() == GL_RGBA);
//}
//
//
//TEST_CASE("GLConversions must return correct pixel type for glm vectors")
//{
//
//
//	SECTION("GLDataType") {
//		
//		CHECK(toGLDataType<uint8_t>() == GL_UNSIGNED_BYTE);
//		CHECK(toGLDataType<int8_t>() == GL_BYTE);
//		CHECK(toGLDataType<uint16_t>() == GL_UNSIGNED_SHORT);
//		CHECK(toGLDataType<int16_t>() == GL_SHORT);
//		CHECK(toGLDataType<uint32_t>() == GL_UNSIGNED_INT);
//		CHECK(toGLDataType<int32_t>() == GL_INT);
//		CHECK(toGLDataType<float>() == GL_FLOAT);
//		CHECK(toGLDataType<double>() == GL_DOUBLE);
//	}
//
//	SECTION("GLFormat")
//	{
//		toGLPixelFormatTestGLM<uint8_t, glm::qualifier::defaultp>();
//		toGLPixelFormatTestGLM<int8_t, glm::qualifier::defaultp>();
//		toGLPixelFormatTestGLM<uint16_t, glm::qualifier::defaultp>();
//		toGLPixelFormatTestGLM<int16_t, glm::qualifier::defaultp>();
//		toGLPixelFormatTestGLM<uint32_t, glm::qualifier::defaultp>();
//		toGLPixelFormatTestGLM<int32_t, glm::qualifier::defaultp>();
//		toGLPixelFormatTestGLM<float, glm::qualifier::defaultp>();
//	}
//	SECTION("GLInternalFormat")
//	{
//		CHECK(toGLInternalPixelFormat<1, uint8_t>() == GL_R8);
//		CHECK(toGLInternalPixelFormat<2, uint8_t>() == GL_RG8);
//		CHECK(toGLInternalPixelFormat<3, uint8_t>() == GL_RGB8);
//		CHECK(toGLInternalPixelFormat<4, uint8_t>() == GL_RGBA8);
//
//		CHECK(toGLInternalPixelFormat<1, int8_t>() == GL_R8);
//		CHECK(toGLInternalPixelFormat<2, int8_t>() == GL_RG8);
//		CHECK(toGLInternalPixelFormat<3, int8_t>() == GL_RGB8);
//		CHECK(toGLInternalPixelFormat<4, int8_t>() == GL_RGBA8);
//
//		CHECK(toGLInternalPixelFormat<1, uint16_t>() == GL_R16UI);
//		CHECK(toGLInternalPixelFormat<2, uint16_t>() == GL_RG16UI);
//		CHECK(toGLInternalPixelFormat<3, uint16_t>() == GL_RGB16UI);
//		CHECK(toGLInternalPixelFormat<4, uint16_t>() == GL_RGBA16UI);
//
//		CHECK(toGLInternalPixelFormat<1, int16_t>() == GL_R16I);
//		CHECK(toGLInternalPixelFormat<2, int16_t>() == GL_RG16I);
//		CHECK(toGLInternalPixelFormat<3, int16_t>() == GL_RGB16I);
//		CHECK(toGLInternalPixelFormat<4, int16_t>() == GL_RGBA16I);
//
//		CHECK(toGLInternalPixelFormat<1, uint32_t>() == GL_R32UI);
//		CHECK(toGLInternalPixelFormat<2, uint32_t>() == GL_RG32UI);
//		CHECK(toGLInternalPixelFormat<3, uint32_t>() == GL_RGB32UI);
//		CHECK(toGLInternalPixelFormat<4, uint32_t>() == GL_RGBA32UI);
//
//		CHECK(toGLInternalPixelFormat<1, int32_t>() == GL_R32I);
//		CHECK(toGLInternalPixelFormat<2, int32_t>() == GL_RG32I);
//		CHECK(toGLInternalPixelFormat<3, int32_t>() == GL_RGB32I);
//		CHECK(toGLInternalPixelFormat<4, int32_t>() == GL_RGBA32I);
//
//		CHECK(toGLInternalPixelFormat<1, float>() == GL_R32F);
//		CHECK(toGLInternalPixelFormat<2, float>() == GL_RG32F);
//		CHECK(toGLInternalPixelFormat<3, float>() == GL_RGB32F);
//		CHECK(toGLInternalPixelFormat<4, float>() == GL_RGBA32F);
//
//		CHECK(toGLInternalPixelFormat<1, float>() == GL_R32F);
//		CHECK(toGLInternalPixelFormat<2, float>() == GL_RG32F);
//		CHECK(toGLInternalPixelFormat<3, float>() == GL_RGB32F);
//		CHECK(toGLInternalPixelFormat<4, float>() == GL_RGBA32F);
//	}
//}
//
//
//
//TEST_CASE("GLTexture2D")
//{
//	// Setup a mock OpenGL Window
//	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
//	auto window = GLWindow(1, 1, "", false);
//
//	auto backend = GpuResourceBackend::get();
//	REQUIRE(backend);
//	REQUIRE(dynamic_cast<GLResourceBackend*>(backend));
//
//
//	SECTION("Creating a texture2D...")
//	{
//		const glm::u8vec4 defaultColor(255, 0, 255, 255);
//		const glm::u32vec2 size(4, 4);
//
//		Texture2D<glm::u8vec4> tex(size, defaultColor);
//		
//		auto backendTexture = tex.getBackendTexture();
//
//		REQUIRE(backendTexture);
//
//		auto glBackendTexture = dynamic_cast<const GLTexture2D*>(backendTexture);
//
//		REQUIRE(backendTexture);
//
//		REQUIRE(backendTexture->isOutdated());
//		REQUIRE(glBackendTexture->handle == 0);
//
//		backend->update(0);
//
//		REQUIRE(!backendTexture->isOutdated());
//		REQUIRE(glBackendTexture->handle > 0);
//	}
//}
//
////TEST_CASE("Initializing the GpuResourceBackend must return a GLResourceBackend")
////{
////	GpuResourceBackend::init<GLResourceBackend>();
////
////
////	auto backend = GpuResourceBackend::get();
////	REQUIRE(backend);
////
////	auto glBackend = dynamic_cast<GLResourceBackend*>(backend);
////
////	REQUIRE(glBackend);
////
////
////	SECTION("Creating a simple Texture2D must also create a GLTexture2D as backendTexture")
////	{
////		Texture2D<glm::u8vec4> tex({ 512, 512 }, { 255, 0, 255, 255 });
////		
////	}
////}
//
//	
