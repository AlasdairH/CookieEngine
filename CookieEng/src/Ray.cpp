#include "Ray.h"

namespace CookieEng
{
namespace Data
{
	Ray::Ray(const glm::vec3 &_origin, const glm::vec3 &_direction)
	{
		origin = _origin;
		direction = glm::normalize(_direction);

		inverseDirection = glm::vec3(1 / direction.x, 1 / direction.y, 1 / direction.z);

		inverseDirection = glm::normalize(inverseDirection);
	}

	glm::vec3 Ray::getPoint(const float _u)
	{
		return origin + direction * _u;
	}
}
}