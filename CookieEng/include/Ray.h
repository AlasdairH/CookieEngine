#pragma once

// cstdlib

// external libs
#include "GLM/common.hpp"

// program

namespace CookieEng
{
namespace Data
{
	struct Ray
	{
	friend class BoundingBox;

	public:
		Ray(const glm::vec3 &_origin, const glm::vec3 &_direction);

		glm::vec3 origin;
		glm::vec3 direction;
		glm::vec3 inverseDirection;
	};
}
}