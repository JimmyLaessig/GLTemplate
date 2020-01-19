#pragma once
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace glm
{
	const glm::vec3 Up		= glm::vec3(0, 0, 1);
	const glm::vec3 Right	= glm::vec3(0, -1, 0);
	const glm::vec3 Forward = glm::vec3(1, 0, 0);
}