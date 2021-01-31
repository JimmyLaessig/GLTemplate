#pragma once
#include "System.h"

namespace Base
{

template<typename FLOAT>
struct GLTEMPLATE_API Rectangle
{

	// Creates a new unique identifier
	/*Rectangle(FLOAT x, FLOAT y, FLOAT width, FLOAT height) :
		mX(x), mY(y), mWidth(width), mHeight(height)
	{}*/

	FLOAT mX, mY, mWidth, mHeight = 0;
};


typedef Rectangle<float> RectangleF;

}