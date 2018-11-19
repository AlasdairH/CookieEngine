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
	/*! @class BoundingBox
	*	@brief An axis aligned bounding box represented by the two minimum and maximum corners
	*
	*	Contains the positional data for the corners of the box as well as the available intersect tests.
	*	The bounding box is not adjusted for the object transform. This must be applied on the getting of the bounding box.
	*/
	class BoundingBox
	{
	public:
		glm::vec3 min = glm::vec3(std::numeric_limits<float>::max());		/**< The minimum corner of the bounding box */
		glm::vec3 max = glm::vec3(std::numeric_limits<float>::min());		/**< The maximum corner of the bounding box */

		/** @brief Tests if the bounding box collides with another bounding box
		*	@return A boolean flag stating if a collision occured or not
		*	@param _other The bounding box to test against
		*
		*	Tests a collision between 'this' bounding box and another. 
		*/
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

		/** @brief Tests if the bounding box collides with a ray
		*	@return A boolean flag stating if a collision occured or not
		*	@param _other The ray to test against
		*
		*	Tests a collision between 'this' bounding box and a ray.
		*/
		bool testCollision(const Ray &_ray)
		{
			double tmin = -INFINITY, tmax = INFINITY;

			for (int i = 0; i < 3; ++i) {
				double t2 = (max[i] - _ray.origin[i]) * _ray.inverseDirection[i];
				double t1 = (min[i] - _ray.origin[i]) * _ray.inverseDirection[i];

				tmin = CNG_MAX(tmin, CNG_MIN(t1, t2));
				tmax = CNG_MIN(tmax, CNG_MAX(t1, t2));
			}

			return tmax > CNG_MAX(tmin, 0.0);
		}
	};
}
}
