#include "CameraController.h"


CameraController::CameraController(const CameraController & other)
{
}

CameraController::CameraController(CameraController && other) noexcept
{
}

CameraController& CameraController::operator=(CameraController && other) noexcept
{
	// TODO: hier Rückgabeanweisung eingeben

	return *this;
}

CameraController& CameraController::operator=(const CameraController & other)
{
	// TODO: hier Rückgabeanweisung eingeben


	return *this;
}

void CameraController::update(float deltaTime)
{	
	
	if (window && camera)
	{
		double currentMousePosX = 0;
		double currentMousePosY = 0;

		glfwGetCursorPos(window, &currentMousePosX, &currentMousePosY);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == 1)
		{
			if (mousePosX >= 0 && mousePosY >= 0)
			{
				auto rotation = camera->transform.getEulerAngles();
				
				auto deltaX = currentMousePosX 	- mousePosX;
				auto deltaY = currentMousePosY 	- mousePosY; 
				camera->transform.setRotation(camera->transform.getEulerAngles() + glm::vec3(0.f, deltaY * 0.2, -deltaX * 0.2));// deltaY * 0.2));
			}

			auto fw = camera->transform.forward();
			auto right = camera->transform.right();

			glm::vec3 delta =
				(glfwGetKey(window, GLFW_KEY_W) ? fw * cameraSpeed : glm::vec3()) +
				(glfwGetKey(window, GLFW_KEY_A) ? -right * cameraSpeed : glm::vec3()) +
				(glfwGetKey(window, GLFW_KEY_S) ? -fw * cameraSpeed : glm::vec3()) +
				(glfwGetKey(window, GLFW_KEY_D) ? right * cameraSpeed : glm::vec3());

			camera->transform.setPosition(camera->transform.getPosition() + delta);
		}

		mousePosX = currentMousePosX;
		mousePosY = currentMousePosY;


	}

}