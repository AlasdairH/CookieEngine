#pragma once

// cstdlib
#include <limits>

// external libs
#include "GLM/common.hpp"
#include "GLM/gtx/common.hpp"

// program
#include "Macro.h"
#include "Ray.h"
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Renderable.h"
#include "PrimativeGenerator.h"

namespace CookieEng
{
namespace Components
{
	class Transform;

	/*! @class BoundingBox
	*	@brief An axis aligned bounding box represented by the two minimum and maximum corners
	*
	*	Contains the positional data for the corners of the box as well as the available intersect tests.
	*	The bounding box is not adjusted for the object transform. This must be applied on the getting of the bounding box.
	*/
	class BoundingBox : public ECS::Component
	{
	public:
		/** @brief Gets the BoundingBox in reference to the object
		*	@return The BoundingBox
		*
		*	Takes the transform component of the parent entity and applies it to a new bounding box from this and then returns it.
		*/
		BoundingBox getBoundingBox();

		/** @brief Pulls size data from an attached mesh component
		*
		*	Looks for a mesh on the parent component and if it has one, pulls the mesh min / max
		*/
		void pullFromMesh();

		/** @brief Gets the minimum bounding point of the AABB
		*	@return The minimum bounding point of the AABB
		*
		*	Gets the minimum bounding point of the AABB
		*/
		inline glm::vec3 getMinBoundingPoint() const { return m_min; }
		/** @brief Gets the maximum bounding point of the AABB
		*	@return The maximum bounding point of the AABB
		*
		*	Gets the maximum bounding point of the AABB
		*/
		inline glm::vec3 getMaxBoundingPoint() const { return m_max; }

		/** @brief Sets the minimum bounding point of the AABB
		*	@param _min The new minimum bounding point of the AABB
		*
		*	Sets the minimum bounding point of the AABB
		*/
		inline void setMinBoundingPoint(const glm::vec3 &_min) { m_min = _min; }
		/** @brief Sets the maximum bounding point of the AABB
		*	@param _max The new maximum bounding point of the AABB
		*
		*	Sets the maximum bounding point of the AABB
		*/
		inline void setMaxBoundingPoint(const glm::vec3 &_max) { m_max = _max; }

		/** @brief Tests if the bounding box collides with another bounding box
		*	@return A boolean flag stating if a collision occured or not
		*	@param _other The bounding box to test against
		*
		*	Tests a collision between 'this' bounding box and another. 
		*/
		bool testCollision(const BoundingBox &_other);

		/** @brief Tests if the bounding box collides with a ray
		*	@return A boolean flag stating if a collision occured or not
		*	@param _ray The ray to test against
		*
		*	Tests a collision between 'this' bounding box and a ray.
		*/
		bool testCollision(const Data::Ray &_ray);

	protected:
		glm::vec3 m_min = glm::vec3(std::numeric_limits<float>::max());		/**< The minimum corner of the bounding box */
		glm::vec3 m_max = glm::vec3(std::numeric_limits<float>::min());		/**< The maximum corner of the bounding box */

		bool m_renderMesh = false;											/**< Flag wether the mesh should render or not */
		Resources::Mesh m_mesh;												/**< Renderable mesh for the bounding box */
	};
}
}
