#pragma once

// cstdlib
#include <limits>

// external libs
#include "GLM/common.hpp"

// program

namespace CookieEng
{
namespace Data
{
	struct BoundingBox
	{
		glm::vec3 min = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
		glm::vec3 max = glm::vec3(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

		bool testCollision(const BoundingBox &_other)
		{
			return	(min.x <= _other.max.x && max.x >= _other.min.x) &&
					(min.y <= _other.max.y && max.y >= _other.min.y) &&
					(min.z <= _other.max.z && max.z >= _other.min.z);
		}
	};
}
}
