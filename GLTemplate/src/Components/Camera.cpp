#include "Components/Camera.h"


Camera::Camera(const Camera & other)
{
}

Camera::Camera(Camera && other) noexcept
{
}

Camera& Camera::operator=(Camera && other) noexcept
{
	// TODO: hier Rückgabeanweisung eingeben
	return *this;
}

Camera& Camera::operator=(const Camera & other)
{
	// TODO: hier Rückgabeanweisung eingeben

	return *this;
}

glm::mat4 Camera::getViewMatrix()
{	
	auto up		= this->transform.up();
	auto pos	= this->transform.getPosition();
	auto fw		= this->transform.forward();

	return glm::lookAt(pos, pos + fw, up);
}


glm::mat4 Camera::getProjectionMatrix()
{
	return glm::mat4();
}
