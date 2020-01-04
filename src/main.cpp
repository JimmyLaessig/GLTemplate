// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include <stdio.h>

#include "GLSLShader.h"
#include "Mesh.h"
#include <iostream>
#include <functional>
#include <numeric>
#include "CameraController.h"

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include<string>

#include "glm/gtx/string_cast.hpp"
#include "Transform.h"
#include "Camera.h"
#define GLM_FORCE_RADIANS
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


struct PerformanceInfo
{
    float frameTimeGPU = 0;
    float frameTimeCPU = 0;
    unsigned int memoryUsageGPU;
    unsigned int memoryUsageCPU;
    unsigned int numPrimitives;
    unsigned int numDrawCalls;
};

void PerformanceOverlay(const PerformanceInfo& info)
{
    ImGui::Begin("Stats");  
    ImGui::Text("Frame Time(GPU): %.3f ms", info.frameTimeGPU / 1000.0f);
    ImGui::Text("Frame Time(CPU): %.3f ms", info.frameTimeCPU / 1000.0f);
    ImGui::Text("Memory used(GPU): MBytes");     
    ImGui::Text("Memory used(CPU): MBytes");  
    ImGui::Text("#Primitives: ");     
    ImGui::Text("#Draw calls: ");     
    ImGui::End();
}


std::vector <std::function<void(int key, int scanCode, bool bShift, bool bAlt, bool bCtrl)>> keyDownCallbacks;
std::vector <std::function<void(int key, int scanCode, bool bShift, bool bAlt, bool bCtrl)>> keyReleasedCallbacks;
std::vector <std::function<void(int key, int scanCode, bool bShift, bool bAlt, bool bCtrl)>> keyRepeatCallbacks;


int main(int, char**)
{
	
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		bool bShift = mods & GLFW_MOD_SHIFT;
		bool bAlt	= mods & GLFW_MOD_ALT;
		bool bCtrl	= mods & GLFW_MOD_CONTROL;
		std::cout << "mods = " << mods << std::endl;
		std::cout << bShift << std::endl;
		std::cout << bAlt << std::endl;
		std::cout << bCtrl << std::endl;

		switch (action)
		{
			case GLFW_PRESS : 
			{
				for (auto& cb : keyDownCallbacks) cb(key, scancode, bShift, bAlt, bCtrl);
				break;
			}
			case GLFW_RELEASE:
			{
				for (auto& cb : keyReleasedCallbacks) cb(key, scancode, bShift, bAlt, bCtrl);
				break;
			}
			case GLFW_REPEAT:
			{
				for (auto& cb : keyRepeatCallbacks) cb(key, scancode, bShift, bAlt, bCtrl);
				break;
			}
			default:
				break;
		}
	});
	
    // Setup Dear ImGui context
    //IMGUI_CHECKVERSION();
   //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    //ImGui_ImplGlfw_InitForOpenGL(window, true);
   // ImGui_ImplOpenGL3_Init(glsl_version);

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

	

	keyDownCallbacks.push_back([](int key, int scancode, bool bShift, bool bAlt, bool bCtrl) 
	{

		std::cout << "key = "<< key << ", bShift = "<<(bShift ? "true" : "false") <<  std::endl;
	});

	keyDownCallbacks.push_back([](int key, int scancode, bool bShift, bool bAlt, bool bCtrl)
	{
		std::cout << "asdasdasd" << std::endl;
		
	});
	

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	
	//auto shader = SharedAsset::FromFile<GLSLShader>("effect.glsl");

	auto shaderRed = SharedAsset::New < GLSLShader>("red");
	{
		ShaderStageData shaderData;
		shaderData.vertexShaderCode =
			"#version 410 core\n"
			"layout(location = 0) in vec3 vPosition;\n"
			"uniform mat4 WorldViewProjectionMatrix;\n"
			"void main()\n"
			"{\n"
			"    gl_Position =  WorldViewProjectionMatrix * vec4(vPosition, 1.0f);\n"
			"}\n";
		shaderData.fragmentShaderCode =
			"#version 410 core\n"
			"layout(location = 0) in vec3 position;\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
			"}\n";

		shaderRed->setShaderStageData(shaderData);
	}

	auto shaderBlue = SharedAsset::New < GLSLShader>("blue");
	{
		ShaderStageData shaderData;
		shaderData.vertexShaderCode =
			"#version 410 core\n"
			"layout(location = 0) in vec3 vPosition;\n"
			"uniform mat4 WorldViewProjectionMatrix;\n"
			"layout(location = 0) out vec3 position;"
			"void main()\n"
			"{\n"
			"    gl_Position =  WorldViewProjectionMatrix * vec4(vPosition, 1.0f);\n"
			"}\n";
		shaderData.fragmentShaderCode =
			"#version 410 core\n"
			"void main()\n"
			"{\n"
			"    gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
			"}\n";

		shaderBlue->setShaderStageData(shaderData);
	}
	
	auto mesh = SharedAsset::New<Mesh>("asdasdasd");// "sibenik-cathedral-vray.obj");

	mesh->subMeshes = std::vector<SubMesh>(1);
	
	SubMeshVertexData data;
	data.positions = {
	   {-1.0, -1.0,  2.0},
	   { 1.0, -1.0,  2.0},
	   { 1.0,  1.0,  2.0},
	   {-1.0,  1.0,  2.0},
	   {-1.0, -1.0, -2.0},
	   { 1.0, -1.0, -2.0},
	   { 1.0,  1.0, -2.0},
	   {-1.0,  1.0, -2.0}
	};
	data.indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	data.normals	= std::vector<glm::vec3>(8);
	data.tangents	= std::vector<glm::vec3>(8);
	data.bitangents = std::vector<glm::vec3>(8);
	data.colors		= std::vector<glm::vec4>(8);
	data.uvs.push_back(std::vector<glm::vec3>(8));
	mesh->subMeshes[0].setVertexData(data);


	shaderRed->updateGpuMemory();
	shaderBlue->updateGpuMemory();

	for (auto& mesh : mesh->subMeshes)
	{
		mesh.updateGpuMemory();
	}


	float lastTime = glfwGetTime();
	float angle = 0;
	
	Transform transformRed;
	Transform transformBlue;
	Camera camera;
	CameraController controller;
	camera.transform.setPosition(glm::vec3(-10, 0, 0));
	
	glm::vec3 pos(0);
	
/*
	keyDownCallbacks.push_back([&](int key, int scanCode, bool bShift, bool bAlt, bool bCtrl) 
	{
		if (key == GLFW_KEY_W)
		{
			pos += glm::vec3(1, 0, 0);
		}
		if (key == GLFW_KEY_S)
		{
			pos += glm::vec3(-1, 0, 0);
		}
	});
*/
	// auto view =  (glm::lookAtLH(glm::vec3(-20, 0, 0), glm::vec3( 0, 0, 0), glm::vec3( 0, 1, 0)));
	Transform animTransform;

	transformRed.setPosition({ 0, -3, 0 });
	transformBlue.setPosition({ 0, 3, 0 });
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        // Start the Dear ImGui frame
        //ImGui_ImplOpenGL3_NewFrame();
       // ImGui_ImplGlfw_NewFrame();
       // ImGui::NewFrame();

       // PerformanceInfo info;

      //  PerformanceOverlay(info);
        

		double time = glfwGetTime();
		double deltaTime = time - lastTime;
		lastTime = time;

		
		controller.update(deltaTime);
		controller.camera = &camera;
		controller.window = window;
		angle += deltaTime * 45;  // 45� per second




		

        //ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
		//glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glm::mat4 projMatrix = glm::perspective(glm::radians(90.0f), (float)display_w / (float)display_h, 0.1f, 1000.0f);

		
		std::shared_ptr<GLSLShader> shaders[2]{ shaderRed, shaderBlue };
		Transform* transforms[2]{ &transformRed, &transformBlue };
		// worldViewProjectionMatrix = anim;
		auto view = camera.getViewMatrix();
		for (int i : { 0, 1 })
		{
			auto worldViewProjectionMatrix = projMatrix * view * transforms[i]->getLocalToWorldMatrix();
			shaders[i]->bind();
			glUniformMatrix4fv(glGetUniformLocation(shaders[i]->programHandle, "WorldViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(worldViewProjectionMatrix));


			for (auto&subMesh : mesh->subMeshes)
			{
				glBindVertexArray(subMesh.VAO);
				glDrawElements(
					GL_TRIANGLES,										// mode
					(GLsizei)subMesh.getVertexData().indices.size(),    // count
					GL_UNSIGNED_INT,   // type
					(void*)0           // element array buffer offset
				);
			}
		}

		
		
		auto error = glGetError();

        glfwSwapBuffers(window);
    }

	//SharedAsset<GLSLShader>::AssetCache.clear();

    // Cleanup
  //  ImGui_ImplOpenGL3_Shutdown();
  //  ImGui_ImplGlfw_Shutdown();
  //  ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    
	return 0;
}
