#include "Ray.h"

namespace CookieEng
{
namespace Data
{
	Ray::Ray(const glm::vec3 &_origin, const glm::vec3 &_direction)
	{
		origin = _origin;
		direction = glm::normalize(_direction);

		for (int i = 0; i < 3; ++i)
		{
			if (direction[i] != 0)
			{
				inverseDirection[i] = 1 / direction[i];
			}
			else
			{
				inverseDirection[i] = 0;
			}
		}
	}

	glm::vec3 Ray::getPoint(const float _u)
	{
		return origin + direction * _u;
	}
}
}