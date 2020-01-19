#pragma once

#include "imgui.h"

class ImGuiWrapper
{
public: 
	virtual void NewFrame() = 0;

	virtual void Render() = 0;
};