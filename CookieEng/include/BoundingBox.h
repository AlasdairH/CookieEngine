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
	};
}
}
