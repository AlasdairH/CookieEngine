#pragma once

// cstdlib
#include <limits>

// external libs
#include "GLM/common.hpp"

// program
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
			return	(min.x <= _other.max.x && max.x >= _other.min.x) &&
					(min.y <= _other.max.y && max.y >= _other.min.y) &&
					(min.z <= _other.max.z && max.z >= _other.min.z);
		}

		bool testCollision(const Ray &_other)
		{

			if ((_other.m_origin.x > max.x) || (_other.m_origin.y > max.y) || (_other.m_origin.z > max.z)
			 || (_other.m_s_xy * max.x - min.y + _other.m_c_xy < 0)
			 || (_other.m_s_yx * max.y - min.x + _other.m_c_yx < 0)
			 || (_other.m_s_zy * max.z - min.y + _other.m_c_zy < 0)
			 || (_other.m_s_yz * max.y - min.z + _other.m_c_yz < 0)
			 || (_other.m_s_xz * max.x - min.z + _other.m_c_xz < 0)
			 || (_other.m_s_zx * max.z - min.x + _other.m_c_zx < 0))
			{
				return false;
			}
			
			return true;
		}
	};
}
}
