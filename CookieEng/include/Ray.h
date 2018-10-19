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

	protected:

		glm::vec3 m_origin;					/**< The origin point */
		glm::vec3 m_direction;				/**< The direction the ray is pointing from the origin */
		glm::vec3 m_inverseDirection;		/**< The inverse of the direction */
		
		float m_s_yx;
		float m_s_xy;
		float m_s_zy;
		float m_s_yz;
		float m_s_xz;
		float m_s_zx;

		float m_c_xy;
		float m_c_yx;
		float m_c_zy;
		float m_c_yz;
		float m_c_xz;
		float m_c_zx;
	};
}
}