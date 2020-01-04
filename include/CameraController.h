#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
#include <glfw3.h>

class CameraController
{
public: 

	CameraController() = default;

	CameraController(const CameraController& other);

	CameraController(CameraController&& other) noexcept;

	CameraController& operator=(CameraController&& other)  noexcept;

	CameraController& operator=(const CameraController& other);

	float cameraSpeed = 2.f;
	
	Camera* camera = nullptr;
	GLFWwindow* window = nullptr;
	void update(float deltaTime);

	double mousePosX = -1;
	double mousePosY = -1;
};