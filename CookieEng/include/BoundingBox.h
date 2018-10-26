#pragma once

// cstdlib
#include <limits>

// external libs
#include "GLM/common.hpp"
#include "GLM/gtx/common.hpp"

// program
#include "Macro.h"
#include "Ray.h"

namespace CookieEng
{
namespace Data
{
	class BoundingBox
	{
	public:
		glm::vec3 min = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
		glm::vec3 max = glm::vec3(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

		bool testCollision(const BoundingBox &_other)
		{
			if (min.x <= _other.max.x && max.x >= _other.min.x)
			{
				if (min.y <= _other.max.y && max.y >= _other.min.y)
				{
					if (min.z <= _other.max.z && max.z >= _other.min.z)
					{
						return true;
					}
				}
			}
			return false;
		}

		bool testCollision(const Ray &_ray)
		{
			double t1 = (min.x - _ray.origin.x) * _ray.inverseDirection.x;
			double t2 = (min.x - _ray.origin.x) * _ray.inverseDirection.x;

			double tmin = CNG_MIN(t1, t2);
			double tmax = CNG_MAX(t1, t2);

			for (int i = 1; i < 3; ++i) {
				t1 = (min[i] - _ray.origin[i]) * _ray.inverseDirection[i];
				t2 = (max[i] - _ray.origin[i]) * _ray.inverseDirection[i];

				tmin = CNG_MAX(tmin, CNG_MIN(t1, t2));
				tmax = CNG_MIN(tmax, CNG_MAX(t1, t2));
			}

			return tmax > CNG_MAX(tmin, 0.0);
		}
	};
}
}
