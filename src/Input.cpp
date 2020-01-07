#include "Input.h"
#include "GLFW/glfw3.h"
#include <assert.h>


std::map<KeyAction, Input::KeyCallbackDelegate> Input::keyCallbacks;


GLFWwindow* Input::window = nullptr;


void Input::init(GLFWwindow * win)
{
	Input::window = win;
	assert(window);

	glfwSetKeyCallback(Input::window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		bool bShift = mods & GLFW_MOD_SHIFT;
		bool bAlt	= mods & GLFW_MOD_ALT;
		bool bCtrl	= mods & GLFW_MOD_CONTROL;

		KeyAction inputAction = (KeyAction)action;
		Key inputKey = (Key) key;

		if (keyCallbacks.count(inputAction))
		{
			auto&&[begin , end] = Input::keyCallbacks.equal_range(inputAction);
			for(auto iter = begin; iter != end; ++iter)
			{
				iter->second(inputKey, scancode, bShift, bAlt, bCtrl);
			}
		}
	});
}


KeyAction Input::getKey(Key key)
{
	assert(window);
	return (KeyAction)glfwGetKey(Input::window, (int)key);
}


KeyAction Input::getMouseButton(MouseButtom btn)
{
	assert(window);
	return (KeyAction)glfwGetMouseButton(Input::window, (int)btn);
}


glm::vec2 Input::getMousePosition()
{
	double currentMousePosX = 0;
	double currentMousePosY = 0;

	glfwGetCursorPos(window, &currentMousePosX, &currentMousePosY);

	return glm::vec2(currentMousePosX, currentMousePosY);
}

void Input::addKeyCallback(KeyAction action, KeyCallbackDelegate delegate)
{
	Input::keyCallbacks.emplace(action, delegate);
}


