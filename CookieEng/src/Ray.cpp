#include "Ray.h"

namespace CookieEng
{
namespace Data
{
	Ray::Ray(const glm::vec3 &_origin, const glm::vec3 &_direction)
	{
		origin = _origin;
		direction = _direction;
		inverseDirection = 1.0f / _direction;
	}
}
}