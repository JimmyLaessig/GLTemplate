#pragma once
#include <glm/glm.hpp>
#include "Components/Camera.h"


class CameraController
{
public: 

	CameraController() = default;


	CameraController(const CameraController& other);


	CameraController(CameraController&& other) noexcept;


	CameraController& operator=(CameraController&& other)  noexcept;


	CameraController& operator=(const CameraController& other);


	void setCamera(Camera* camera);
	

	void update(float deltaTime);

private:

	Camera* camera = nullptr;

	float cameraSpeed = 1.f;

	glm::vec2 mousePos = glm::vec2(0);
	glm::vec3 eulerAngles = glm::vec3(0);

	bool bInitialized = false;
};