// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)



//#include <stdio.h>
//
//#include <iostream>
//#include <functional>
//#include <numeric>
//#include <set>
//#include <string>
//#include "Stopwatch.h"
//#include "Rendering/GL/GLSLShader.h"
//#include "Rendering/Mesh.h"
//#include "CameraController.h"
//#include "Rendering/GpuResourceBackend.h"
//#include "Rendering/Renderer.h"
//#include "Application/Input.h"
//#include "Application/UI.h"
//#include "glm/gtx/string_cast.hpp"
//#include "Transform.h"
//#include "Rendering/Camera.h"
//#include "Application/Window.h"
//#include "Rendering/Texture2D.h"

#include "imgui.h"
#include "Application/GL/GLWindow.h"
#include<iostream>
#include "Components/Camera.h"
#include "CameraController.h"
#include "SharedAsset.h"
#include "Components/Mesh.h"
#include "Rendering/Renderer.h"
#include "Components/Texture2D.h"

//#define GLM_FORCE_RADIANS
//// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
//// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
//// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
//#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
//#pragma comment(lib, "legacy_stdio_definitions")
//#endif
//
//static void glfw_error_callback(int error, const char* description)
//{
//	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}
//
//
//struct PerformanceInfo
//{
//	float frameTime			= 0;
//    float frameTimeGPU		= 0;
//    unsigned int numRenderObjects;
//};
//
//
//void PerformanceOverlay(const PerformanceInfo& info)
//{
//    ImGui::Begin("Stats");  
//	ImGui::Text("Frame Time(CPU): %.5f ms", info.frameTime);
//	ImGui::Text("Frame Time(GPU): %.5f ms", info.frameTimeGPU);
//	ImGui::Text("#render objects: ", info.numRenderObjects);
//    ImGui::End();
//}



int main(int, char**)
{
	GLWindow window(1024u, 768u, "Test", false);

	window.OnWindowResizedDelegate.subscribe([](auto size)
	{
		std::cout << size.x << ", " << size.y << std::endl;
	});

	window.OnFrameUpdateDelegate.subscribe([](auto deltaTime)
	{
		std::cout << deltaTime << std::endl;

		ImGui::Begin("Stats");  
		//ImGui::Text("Frame Time(CPU): %.5f ms", info.frameTime);
		ImGui::Text("Frame Time(GPU): %.5f ms", deltaTime);
		//ImGui::Text("#render objects: ", info.numRenderObjects);
		ImGui::End();
	});

	// Setup camera
	
	Camera camera;
	camera.transform.setPosition(glm::vec3(-10, 0, 0));
	CameraController controller;
	controller.setCamera(&camera);
	window.OnFrameUpdateDelegate.subscribe([&](float deltaTime) {controller.update(deltaTime); });
	
	
	// Setup mesh
	
	auto mesh = SharedAsset::FromFile<Mesh, MeshLoader>("Assets/Models/sibenik-cathedral-vray.obj", "");
	
	window.OnFrameUpdateDelegate.subscribe([&](float deltaTime)
	{
		for (auto& submesh : mesh->subMeshes)
		{
			GpuResourceBackend::get()->getRenderer()->submitOneTimeRenderObject(
				{
					submesh.get(),
					Transform(),
					nullptr,
					nullptr,
					0
				});
		}
	});
	

	Texture2D<glm::u8vec4> tex({ 512, 512 }, glm::u8vec4(255, 0, 255, 255));

	window.run();

	return 0;
}

    // Setup window
//    glfwSetErrorCallback(glfw_error_callback);
//    if (!glfwInit())
//        return 1;
//
//    // Decide GL+GLSL versions
//#if __APPLE__
//    // GL 3.2 + GLSL 150
//    const char* glsl_version = "#version 150";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
//#else
//    // GL 3.0 + GLSL 130
//    const char* glsl_version = "#version 410";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
//#endif

    // Create window with graphics context
//    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
//
//    if (window == NULL)
//        return 1;
//    glfwMakeContextCurrent(window);
//    //glfwSwapInterval(1); // Enable vsync
//	//Input::init(window);
//    // Initialize OpenGL loader
////#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
////    bool err = gl3wInit() != 0;
////#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//    bool err = glewInit() != GLEW_OK;
////#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
////    bool err = gladLoadGL() == 0;
////#else
////    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
////#endif
//    if (err)
//    {
//		std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
//        return 1;
//    }

	//std::unique_ptr<UI> ui = std::unique_ptr<UI>(new UI(window));
	
    //Setup Dear ImGui context
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();


    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io .ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style


    //ImGui::StyleColorsDark();


   // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings


	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

	

	//keyDownCallbacks.push_back([](int key, int scancode, bool bShift, bool bAlt, bool bCtrl) 
	//{
	//	std::cout << "key = "<< key << ", bShift = "<<(bShift ? "true" : "false") <<  std::endl;
	//});

	//keyDownCallbacks.push_back([](int key, int scancode, bool bShift, bool bAlt, bool bCtrl)
	//{
	//	std::cout << "asdasdasd" << std::endl;
	//});
	
	/*auto x1 = getGLPixelFormat<glm::vec3>();
	auto x2 = getGLPixelFormat<glm::vec2>();
	auto x3 = getGLPixelFormat<glm::dvec2>();
	auto x4 = getGLPixelFormat<glm::uvec4>();
	auto x5 = getGLPixelFormat<glm::vec1>();*/
	//auto x6 = getGLDataType<glm::vec3>() == GL_FLOAT;
 //   // Our state
 //   ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	////auto shader = SharedAsset::FromFile<GLSLShader>("effect.glsl");

	//auto shaderRed = SharedAsset::New<GLSLShader>("red");
	//{
	//	ShaderStageData shaderData;
	//	shaderData.vertexShaderCode =
	//		"#version 410 core\n"
	//		"layout(location = 0) in vec3 vPosition;\n"
	//		"uniform mat4 WorldViewProjectionMatrix;\n"
	//		"void main()\n"
	//		"{\n"
	//		"    gl_Position =  WorldViewProjectionMatrix * vec4(vPosition, 1.0f);\n"
	//		"}\n";
	//	shaderData.fragmentShaderCode =
	//		"#version 410 core\n"
	//		"layout(location = 0) in vec3 position;\n"
	//		"uniform sampler2D tex;\n"
	//		"void main()\n"
	//		"{\n"
	//		"    gl_FragColor = vec4(texture(tex, vec2(0.0f, 0.0f)).rgb, 1.0f);// vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
	//		"}\n";

	//	shaderRed->setShaderStageData(shaderData);
	//}

	//auto shaderBlue = SharedAsset::New<GLSLShader>("blue");
	//{
	//	ShaderStageData shaderData;
	//	shaderData.vertexShaderCode =
	//		"#version 410 core\n"
	//		"layout(location = 0) in vec3 vPosition;\n"
	//		"uniform mat4 WorldViewProjectionMatrix;\n"
	//		"layout(location = 0) out vec3 position;"
	//		"void main()\n"
	//		"{\n"
	//		"    gl_Position =  WorldViewProjectionMatrix * vec4(vPosition, 1.0f);\n"
	//		"}\n";
	//	shaderData.fragmentShaderCode =
	//		"#version 410 core\n"
	//		"void main()\n"
	//		"{\n"
	//		"    gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
	//		"}\n";

	//	shaderBlue->setShaderStageData(shaderData);
	//}


	//auto mesh = SharedAsset::New<Mesh>("sibenik-cathedral-vray.obj");
	//
	//IndexedGeometryData data;
	//data.positions = {
	//   {-1.0, -1.0,  2.0},
	//   { 1.0, -1.0,  2.0},
	//   { 1.0,  1.0,  2.0},
	//   {-1.0,  1.0,  2.0},
	//   {-1.0, -1.0, -2.0},
	//   { 1.0, -1.0, -2.0},
	//   { 1.0,  1.0, -2.0},
	//   {-1.0,  1.0, -2.0}
	//};
	//
	//data.indices = {
	//	// front
	//	0, 1, 2,
	//	2, 3, 0,
	//	// right
	//	1, 5, 6,
	//	6, 2, 1,
	//	// back
	//	7, 6, 5,
	//	5, 4, 7,
	//	// left
	//	4, 0, 3,
	//	3, 7, 4,
	//	// bottom
	//	4, 5, 1,
	//	1, 0, 4,
	//	// top
	//	3, 2, 6,
	//	6, 7, 3
	//};
	//data.normals	= std::vector<glm::vec3>(8, glm::vec3(0));
	//data.tangents	= std::vector<glm::vec3>(8, glm::vec3(0));
	//data.bitangents = std::vector<glm::vec3>(8, glm::vec3(0));
	//data.colors		= std::vector<glm::vec4>(8, glm::vec4(0));
	//data.uvs.push_back(std::vector<glm::vec3>(8, glm::vec3(0)));

	//mesh->addSubMesh(data, nullptr);	
	//
	//Camera camera;
	//CameraController controller;
	//controller.setCamera(&camera);

	//camera.transform.setPosition(glm::vec3(-10, 0, 0));
	////GLTexture2D<glm::u8vec4>tex({ 100, 100 }, glm::u8vec4(255, 0, 255, 255));
	//Transform transformRed;
	//Transform transformBlue;
	//transformRed.setPosition({ 0, -3, 0 });
	//transformBlue.setPosition({ 0, 3, 0 });

	//PerformanceInfo perfInfo;

	//float lastTime = (float)glfwGetTime();
	//int display_w, display_h;
 //   // Main loop
 //   while (!glfwWindowShouldClose(window))
 //   {
	//	
 //       // Poll and handle events (inputs, window resize, etc.)
 //       // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
 //       // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
 //       // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
 //       // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
 //       glfwPollEvents();
	//	glfwGetFramebufferSize(window, &display_w, &display_h);

	//	// Calculate delta time
	//	float time = (float)glfwGetTime();
	//	float deltaTime = time - lastTime;
	//	lastTime = time;
	//	perfInfo.frameTime = deltaTime * 1000.f;
	//	// Temporary update code
	//	ui->update(deltaTime);
	//	GpuResourceBackend::get()->update(deltaTime);
	//	controller.update(deltaTime);

	//	// Test UI
	//	PerformanceOverlay(perfInfo);
 //       
	//	// Render prep code
 //       glViewport(0, 0, display_w, display_h);
 //       glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
 //       glClear(GL_COLOR_BUFFER_BIT);
	//	//glDisable(GL_CULL_FACE);
	//	glDisable(GL_DEPTH_TEST);


		//if (auto renderer = GpuResourceBackend::get()->getRenderer())
		//{
		//	// Create the render view for this frame
		//	RenderView rw
		//	{
		//		camera.getViewMatrix(),
		//		glm::perspective(glm::radians(90.0f), (float)display_w / (float)display_h, 0.1f, 1000.0f)
		//	};
		//	stopwatch::Stopwatch gpuWatch;
		//	gpuWatch.start();
		//	// Temporary code to construct render objects each frame
		//	renderer->submitOneTimeRenderObject(ui->toRenderObject());
		//	unsigned int numRenderObjects = 1;

		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, tex.handle);
		//	glUniform1i(glGetUniformLocation(shaderRed->programHandle, "tex"), 0);
		//	for (auto& sm : mesh->subMeshes)
		//	{
		//		RenderObject ro(
		//			sm.get(),
		//			transformRed,
		//			shaderRed.get(),
		//			nullptr,
		//			0
		//		);
		//		numRenderObjects++;
		//		renderer->submitOneTimeRenderObject(ro);
		//	}
		//	
		//	// Execute all render jobs
		//	renderer->executeRenderJobs(rw);
		//	perfInfo.frameTimeGPU = (float)gpuWatch.elapsed();
		//	perfInfo.numRenderObjects = numRenderObjects;
		//}
		//

		//auto error = glGetError();

  //      glfwSwapBuffers(window);
  //  }

	//SharedAsset<GLSLShader>::AssetCache.clear();

    // Cleanup


    ////glfwDestroyWindow(window);
    ////glfwTerminate();

    
