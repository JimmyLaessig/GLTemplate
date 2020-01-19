#pragma once
#include <glm/glm.hpp>
#include "Transform.h"
#include "Rendering/Renderer.h"
#include "imgui.h"



class UI: public DrawableGpuResource
{
public: 


	UI(struct GLFWwindow* window);


	virtual ~UI();
	

	RenderObject toRenderObject();
	

	void update(float deltaTime);


	virtual std::function<void()> getDrawCall() const override;


	virtual void updateGpuMemory_Internal() {};


	virtual void freeGpuMemory_Internal() {};
};