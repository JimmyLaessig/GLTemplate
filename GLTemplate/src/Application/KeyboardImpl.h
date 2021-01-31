#pragma once

#include "Application/Keyboard.h"
//#include "Application/Input.h"

#include "Rendering/GL/OpenGL.h"


namespace Application
{


class KeyboardImpl
{
public:

	
	KeyState getKeyState(Key) const;


	bool isKeyDown(Key key) const;


	bool isKeyUp(Key key) const;


	bool isKeyPressed(Key key) const;


private:

	std::shared_ptr<GLFWwindow> mWindowHandle;
};

}