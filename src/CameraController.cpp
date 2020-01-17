#include "CameraController.h"
#include <iostream>
#include "Application/Input.h"

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

void CameraController::setCamera(Camera * camera)
{
	this->camera		= camera;
	this->eulerAngles	= camera->transform.getEulerAngles();
}

void CameraController::update(float deltaTime)
{	
//	if (camera)
//	{
//		if (!bInitialized)
//		{
//			mousePos = Input::getMousePosition();
//			bInitialized = true;
//		}
//
//		auto currentMousePos = Input::getMousePosition();
//
//		if (Input::getMouseButton(MouseButtom::BUTTON_2) == KeyAction::PRESS)
//		{
//			{
//				eulerAngles.x = 0;
//				eulerAngles.y += (float)(mousePos.y - currentMousePos.y) * 0.2f;
//				eulerAngles.z += (float)(mousePos.x - currentMousePos.x) * 0.2f;
//				eulerAngles.y = glm::clamp(eulerAngles.y, -89.9f, 89.9f);
//
//				if (eulerAngles.z >= 360.0f)
//				{
//					eulerAngles.z -= 360.0f;
//				}
//				if (eulerAngles.z < 0.0f)
//				{
//					eulerAngles.z += 360.0f;
//				}
//
//				// Rotate around up axis
//				auto rotZ = glm::angleAxis(glm::radians(eulerAngles.z), glm::Up);
//				// Rotate y-axis around the rotated z-axis
//				auto yAxis = rotZ * glm::Right;
//				// Rotate around rotated yAxis
//				auto rotY = glm::angleAxis(glm::radians(eulerAngles.y), yAxis);
//				
//				camera->transform.setRotation(rotY * rotZ);
//			}
//
//			{
//				auto fw = camera->transform.forward();
//				auto right = camera->transform.right();
//
//				glm::vec3 delta = glm::vec3(0);
//		/*			(Input::getKey(Key::W) == KeyAction::PRESS ? fw * cameraSpeed : glm::vec3(0.f)) +
//					(Input::getKey(Key::A) == KeyAction::PRESS ? -right * cameraSpeed : glm::vec3(0.f)) +
//					(Input::getKey(Key::S) == KeyAction::PRESS ? -fw * cameraSpeed : glm::vec3(0.f)) +
//					(Input::getKey(Key::D) == KeyAction::PRESS ? right * cameraSpeed : glm::vec3(0.f));
//*/
//				camera->transform.setPosition(camera->transform.getPosition() + delta);
//			}
//		}
//
//		mousePos = currentMousePos;
//	}
}