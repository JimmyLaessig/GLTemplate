#include "Transform.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#define GLM_FORCE_RADIANS




Transform::Transform(const Transform & other)
{
	this->position		= other.position;
	this->scale			= other.scale;
	//this->rotation		= other.rotation;
	this->eulerAngles = other.eulerAngles;
	this->bOutdated = true;
}


Transform::Transform(Transform && other) noexcept
{
	this->position		= std::move(other.position);
	this->scale			= std::move(other.scale);
	///this->rotation		= std::move(other.rotation);
	this->eulerAngles	= std::move(other.eulerAngles);
	this->bOutdated = true;
}


Transform& Transform::operator=(Transform && other) noexcept
{
	this->position		= std::move(other.position);
	this->scale			= std::move(other.scale);
	///this->rotation		= std::move(other.rotation);
	this->eulerAngles = std::move(other.eulerAngles);
	this->bOutdated		= true;
	return *this;
}


Transform& Transform::operator=(const Transform & other)
{
	this->position		= other.position;
	this->scale			= other.scale;
	///this->rotation		= other.rotation;
	this->eulerAngles = other.eulerAngles;
	this->bOutdated		= true;
	return *this;
}


glm::mat4 Transform::getLocalToWorldMatrix() const
{
	computeMatrices();
	return localToWorldMatrix;
}


glm::mat4 Transform::getWorldToLocalMatrix() const
{
	computeMatrices();
	return worldToLocalMatrix;
}


glm::mat4 Transform::getLocalToWorldNormalMatrix() const
{
	computeMatrices();
	return localToWorldNormalMatrix;
}


const glm::vec3 Transform::getPosition() const
{
	return position;
}


const glm::vec3 Transform::getEulerAngles() const
{
	//return glm::eulerAngles(rotation);
	return eulerAngles;
}


const glm::quat Transform::getRotation() const
{
	//return rotation;
	return glm::quat();
}


const glm::vec3 Transform::getScale() const
{
	return scale;
}


void Transform::setScale(const glm::vec3 & scale)
{
	this->scale		= scale;
	this->bOutdated	= true;
}


void Transform::setPosition(const glm::vec3 & position)
{
	this->position	= position;
	this->bOutdated = true;
}


void Transform::setRotation(const glm::quat & rotation)
{
	//this->rotation	= rotation;	
	this->bOutdated = true;
}
 

void Transform::setRotation(const glm::vec3 & eulerAngles)
{
	// this->rotation	= glm::quat(glm::orientate3(glm::radians(eulerAngles)));		
	this->eulerAngles = eulerAngles;
	this->bOutdated = true;
}


void Transform::setPositionAndRotation(const glm::vec3 & position, const glm::vec3 & eulerAngles)
{
	setPosition(position);
	setRotation(eulerAngles);
}


void Transform::setPositionAndRotation(const glm::vec3 & position, const glm::quat & rotation)
{
	setPosition(position);
	setRotation(rotation);
}


void Transform::setPositionRotationAndScale(const glm::vec3 & position, const glm::vec3 & eulerAngles, const glm::vec3 & scale)
{
	setPosition(position);
	setRotation(eulerAngles);
	setScale(scale);
}


void Transform::setPositionRotationAndScale(const glm::vec3 & position, const glm::quat & rotation, const glm::vec3 & scale)
{
	setPosition(position);
	setRotation(rotation);
	setScale(scale);
}


glm::vec3 Transform::forward() const
{
	return  glm::normalize(glm::vec3(getLocalToWorldMatrix() * glm::vec4(1, 0, 0, 1)) - position);
}


glm::vec3 Transform::up() const
{
	return  glm::normalize(glm::vec3(getLocalToWorldMatrix() * glm::vec4(0, 0, 1, 1)) - position);
}


glm::vec3 Transform::right() const
{
	return glm::normalize(glm::vec3(getLocalToWorldMatrix() * glm::vec4(0, -1, 0, 1)) - position);
}


void Transform::computeMatrices() const
{
	if (bOutdated)
	{
		bOutdated = false;
		auto T = glm::translate(position);
		//auto R = glm::toMat4(rotation);	
		glm::mat4 R =
			glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))*
			glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0));
		auto S = glm::scale(scale);

		this->localToWorldMatrix		= T * R * S;
		this->worldToLocalMatrix		= glm::inverse(localToWorldMatrix);
		this->localToWorldNormalMatrix	= glm::mat3(glm::transpose(worldToLocalMatrix));
	}
}
