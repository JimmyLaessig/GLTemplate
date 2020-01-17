#include "Application/GLFW/GLFWWindow.h"
#include "glfw3.h"
GLFWWindow::~GLFWWindow()
{
}

KeyState GLFWWindow::getKeyState(Key key)
{
	return (KeyState)glfwGetKey(glfwWindow, (int)key);
}

KeyState GLFWWindow::getMouseButtonState(MouseButtom button)
{
	return (KeyState)glfwGetMouseButton(glfwWindow, (int)button);
}

glm::vec2 GLFWWindow::getCursorPosition()
{
	double posX, posY;
	glfwGetCursorPos(glfwWindow, &posX, &posY);
	return glm::vec2((float)posX, (float)posY);
}

void GLFWWindow::updateWindow(float deltaTime)
{

}

bool GLFWWindow::windowShouldClose()
{
	return glfwWindowShouldClose(glfwWindow) == 0;
}
