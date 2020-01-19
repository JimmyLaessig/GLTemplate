#pragma once

#include "Application/Window.h"



class GLFWWindow : public IWindow
{

	GLFWWindow(size_t width, size_t height, bool bFullscreen);

	virtual ~GLFWWindow();


	// Inherited via IWindow
	virtual KeyState getKeyState(Key key) override;


	virtual KeyState getMouseButtonState(MouseButtom button) override;



	virtual glm::vec2 getCursorPosition() override;


	virtual void updateWindow(float deltaTime) override;


	virtual glm::vec2 getCursorPosition() override;


	virtual bool windowShouldClose() override;


private: 

	struct GLFWwindow* glfwWindow;
};