#include "Application/GL/GLWindow.h"
#include <iostream>

#include "GLFW/glfw3.h"
#include "Rendering/GL/GLResourceBackend.h"
#include "Application/GL/ImguiWrapperGL.h"

void glfwErrorCallback(int error, const char* description)
{
	std::cerr << "Glfw Error "<< error << ": " << description<< "\n";
	
}


GLWindow::GLWindow(unsigned int width, unsigned int height, const std::string& title, bool bFullscreen) 
	: IWindow(width, height, bFullscreen)
{
	// Setup window
	glfwSetErrorCallback(glfwErrorCallback);

	if (!glfwInit())
		throw 1;

	const char* glsl_version = "#version 410";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Create window with graphics context
	glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (glfwWindow == NULL)
		throw 1;
	glfwMakeContextCurrent(glfwWindow);

	//glfwSwapInterval(1); // Enable vsync
	//Input::init(window);

	

	GpuResourceBackend::init<GLResourceBackend>();

	imGuiWrapper = std::make_unique<ImGuiWrapperGL>(glfwWindow);
}


GLWindow::~GLWindow()
{
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}


KeyState GLWindow::getKeyState(Key key) const
{
	return (KeyState)glfwGetKey(glfwWindow, (int)key);
}


KeyState GLWindow::getMouseButtonState(MouseButtom button) const
{
	return (KeyState)glfwGetMouseButton(glfwWindow, (int)button);
}


glm::vec2 GLWindow::getCursorPosition() const
{
	double posX, posY;
	glfwGetCursorPos(glfwWindow, &posX, &posY);
	return glm::vec2(posX, posY);
}


void GLWindow::prepareUpdate(float deltaTime)
{
	glfwPollEvents();
	int width, height;
	glfwGetFramebufferSize(glfwWindow, &width, &height);
	auto size = getSize();
	if (width != size.x || height != size.y)
	{
		resize({ width, height });
	}
	
}


bool GLWindow::windowShouldClose() const
{
	return glfwWindowShouldClose(glfwWindow) == GLFW_TRUE;
}

void GLWindow::prepareRender()
{
	
	glViewport(0, 0, getSize().x, getSize().y);
	
	    
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
   	//	glDisable(GL_CULL_FACE);
	//	glDisable(GL_DEPTH_TEST);

}

void GLWindow::finishRender()
{
	glfwSwapBuffers(glfwWindow);
}