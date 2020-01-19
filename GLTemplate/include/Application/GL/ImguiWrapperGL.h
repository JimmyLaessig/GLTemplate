#pragma once

#include "Application/ImguiWrapper.h"

class ImGuiWrapperGL : public ImGuiWrapper
{
public: 
	ImGuiWrapperGL::ImGuiWrapperGL(struct GLFWwindow* window);

	virtual ImGuiWrapperGL::~ImGuiWrapperGL();


	virtual void NewFrame() override;


	virtual void Render() override;

};