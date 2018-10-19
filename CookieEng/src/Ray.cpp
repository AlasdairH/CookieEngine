#include "Ray.h"

namespace CookieEng
{
namespace Data
{
	Ray::Ray(const glm::vec3 &_origin, const glm::vec3 &_direction)
	{
		m_origin = _origin;
		m_direction = _direction;

		m_inverseDirection = 1.0f / _direction;

		// slope calculation
		m_s_yx = m_direction.x * m_inverseDirection.y;
		m_s_xy = m_direction.y * m_inverseDirection.x;
		m_s_zy = m_direction.y * m_inverseDirection.z;
		m_s_yz = m_direction.z * m_inverseDirection.y;
		m_s_xz = m_direction.x * m_inverseDirection.z;
		m_s_zx = m_direction.z * m_inverseDirection.x;

		// precomputation
		m_c_xy = m_origin.y - m_s_xy * m_origin.x;
		m_c_yx = m_origin.x - m_s_yx * m_origin.y;
		m_c_zy = m_origin.y - m_s_zy * m_origin.z;
		m_c_yz = m_origin.z - m_s_yz * m_origin.y;
		m_c_xz = m_origin.z - m_s_xz * m_origin.x;
		m_c_zx = m_origin.x - m_s_zx * m_origin.z;
	}
}
}