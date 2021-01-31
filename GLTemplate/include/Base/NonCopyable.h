#pragma once
#include "Base/System.h"

namespace Base
{
// Objects that inherit from this cannot be copied. 
// They can only be moved.
class GLTEMPLATE_API NonCopyable
{
public:

	NonCopyable() = default;

	virtual ~NonCopyable() = default;

	NonCopyable& operator=(const NonCopyable& other) = delete;

	NonCopyable(const NonCopyable& other) = delete;
};
}