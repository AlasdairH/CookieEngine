#pragma once

// cstdlib
#include <vector>

// external libs
#include "GLM/glm.hpp"

// program
#include "Mesh.h"

namespace CookieEng
{
namespace Data
{
	class PrimativeGenerator
	{
	public:
		static Resources::Mesh generateCube(const glm::vec3 &_min, const glm::vec3 &_max);
	};
}
}