#pragma once

#include <functional>
#include <map>

#include "uuid.h"

#include "VectorMath.h"
#include "Application/Input.h"
#include "Application/Delegates.h"


typedef std::function<void(float)> OnUpdateCallback;
typedef std::function<void(size_t, size_t)> OnResizedDelegate;
typedef std::function<void(size_t, size_t)> OnWindowCloseDelegate;
typedef std::function<void(Key key, int scanCode, bool bShift, bool bAlt, bool bCtrl)> KeyCallbackDelegate;



class IWindow
{

public: 

	IWindow(unsigned int width, unsigned int height, bool bFullscreen = false);


	IWindow() = delete;


	IWindow(const IWindow& other) = delete;


	Delegate<OnUpdateCallback> OnFrameUpdateDelegate;


	Delegate<OnUpdateCallback> OnWindowResizedDelegate;


	Delegate< KeyCallbackDelegate> OnKeyPressedDelegate;

	/**
	 * Gets the last know state of the key.
	 * @return Returns either Input::KeyAction::PRESSED or Input::KeyAction::RELEASE
	 */
	virtual KeyState getKeyState(Key key) = 0;

	/**
	 * Gets the last know state of the mouse button.
	 * @return Returns either Input::KeyAction::PRESSED or Input::KeyAction::RELEASE
	 */
	virtual KeyState getMouseButtonState(MouseButtom button) = 0;

	/**
	 * Returns the mouse position in screen coordinates relative to the upper-right corner.
	 */
	virtual glm::vec2 getCursorPosition() = 0;


	virtual void updateWindow(float deltaTime) = 0;

private: 

	virtual bool windowShouldClose() = 0;


	glm::u32vec2 size;


	bool bFullscreen;


	virtual void run();
};