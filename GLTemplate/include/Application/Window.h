#pragma once

#include <functional>
#include <map>

#include "VectorMath.h"
#include "Application/ImGuiWrapper.h"
#include "Application/Input.h"
#include "Application/Delegates.h"

typedef std::function<void(float)> OnUpdateCallback;
typedef std::function<void(glm::u32vec2)> OnResizedDelegate;
typedef std::function<void(size_t, size_t)> OnWindowCloseDelegate;
typedef std::function<void(Key key, int scanCode, bool bShift, bool bAlt, bool bCtrl)> KeyCallbackDelegate;


class IWindow
{

public: 

	IWindow(unsigned int width, unsigned int height, bool bFullscreen = false);


	IWindow() = delete;


	IWindow(const IWindow& other) = delete;


	Delegate<OnUpdateCallback> OnFrameUpdateDelegate;


	Delegate<OnResizedDelegate> OnWindowResizedDelegate;


	Delegate< KeyCallbackDelegate> OnKeyPressedDelegate;

	/**
	 * Gets the last know state of the key.
	 * @return Returns either Input::KeyAction::PRESSED or Input::KeyAction::RELEASE
	 */
	virtual KeyState getKeyState(Key key) const = 0;

	/**
	 * Gets the last know state of the mouse button.
	 * @return Returns either Input::KeyAction::PRESSED or Input::KeyAction::RELEASE
	 */
	virtual KeyState getMouseButtonState(MouseButtom button) const = 0;

	/**
	 * Returns the mouse position in screen coordinates relative to the upper-right corner.
	 */
	virtual glm::vec2 getCursorPosition() const = 0;




	/**
	 *
	 */
	virtual void run();

	/**
	 *
	 */
	virtual glm::u32vec2 getSize() const
	{
		return this->size;
	}

	/**
	 *
	 */
	virtual void resize(const glm::u32vec2& size)
	{
		this->size = size;
		OnWindowResizedDelegate.broadcast(this->size);
	}


protected: 

	/**
	 *
	 */
	virtual void prepareUpdate(float deltaTime) = 0;

	/**
	 * maybe do clear the backbuffer
	 */
	virtual void prepareRender() = 0;

	/**
	 * Do swap buffers and stuff
	 */
	virtual void finishRender() = 0;


	/**
	 *
	 */
	virtual bool windowShouldClose() const = 0;


	std::unique_ptr<ImGuiWrapper> imGuiWrapper;

private: 

	glm::u32vec2 size;

	bool bFullscreen;
};