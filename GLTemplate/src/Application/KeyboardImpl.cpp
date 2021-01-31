#include "KeyboardImpl.h"

#include "GLFW/Context.h"


namespace Application
{

KeyState
KeyboardImpl::getKeyState(Key key) const
{
	//glfwGetKey(mWindowHandle.get(), )
	return KeyState::PRESSED;
}


bool
KeyboardImpl::isKeyDown(Key key) const
{
	return KeyState::PRESSED == getKeyState(key);
}


bool
KeyboardImpl::isKeyUp(Key key) const
{
	return KeyState::RELEASED == getKeyState(key);
}


bool
KeyboardImpl::isKeyPressed(Key key) const
{
	return false;
}


}