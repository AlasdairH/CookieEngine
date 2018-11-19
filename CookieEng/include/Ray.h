#pragma once

// cstdlib

// external libs
#include "GLM/common.hpp"
#include "GLM/geometric.hpp"

// program

namespace CookieEng
{
namespace Data
{
	/*! @class Ray
	*	@brief A ray represented by an origin point and a direction for an infinite distance
	*
	*	Represents a ray with on origin point and direction for an infinite distance. This can be tested against various bounds for collision. (See BoundingBox)
	*/
	struct Ray
	{
	friend class BoundingBox;

	public:
		/** @brief Ray Ctor. Creates a ray from the specified parameters
		*	@param _origin The origin point of the ray
		*	@param _direction The direction the ray travels
		*
		*	Creates a ray from the specified parameters.
		*/
		Ray(const glm::vec3 &_origin, const glm::vec3 &_direction);

		/** @brief Ray Ctor. Creates a ray from the specified parameters
		*	@return The point in world space along a ray at distance _u
		*	@param _u How far along the ray to get the point from. Can be positive for negative.
		*
		*	Gets a point along the ray at a specified distance from the origin along the direction.
		*/
		glm::vec3 getPoint(const float _u);


		glm::vec3	origin;				/**< The origin point of the ray */
		glm::vec3	direction;			/**< The direction of the ray */
		glm::vec3	inverseDirection;	/**< The pre-computed inverse direction of the ray */
	};
}
}