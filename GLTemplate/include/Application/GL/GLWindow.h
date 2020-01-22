#pragma once

#include "Application/Window.h"
#include "Rendering/GL/GL.h"

/**
 *
 */
class GLWindow : public IWindow
{
public: 

	/**
	 *
	 */
	GLWindow(unsigned int width, unsigned int height, const std::string& title, bool bFullscreen);

	/**
	 *
	 */
	virtual ~GLWindow();

	/**
	 *
	 */
	virtual KeyState getKeyState(Key key)  const override;

	/**
	 *
	 */
	virtual KeyState getMouseButtonState(MouseButtom button)  const override;

	/**
	 *
	 */
	virtual glm::vec2 getCursorPosition()  const override;

	/**
	 *
	 */
	virtual void prepareUpdate(float deltaTime) override;

	/**
	 *
	 */
	virtual bool windowShouldClose()  const override;

protected:

	/**
	 * maybe do clear the backbuffer
	 */
	virtual void prepareRender() override;

	/**
	 * Do swap buffers and stuff
	 */
	virtual void finishRender() override;


private: 

	/**
	 *
	 */
	struct GLFWwindow* glfwWindow;

};