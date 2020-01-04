#pragma once
#include <glm/glm.hpp>
#include "Transform.h"


class Camera
{
public: 

	Camera() = default;

	Camera(const Camera& other);

	Camera(Camera&& other) noexcept;

	Camera& operator=(Camera&& other)  noexcept;

	Camera& operator=(const Camera& other);

	glm::mat4 getViewMatrix();

	glm::mat4 getProjectionMatrix();

	float fieldOfView;

	float ratio;

	float nearPlane;

	float farPlane;

	Transform transform;
	
};