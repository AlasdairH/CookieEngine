#pragma once

// cstdlib


// external libs
#include "GLM/glm.hpp"
#include "GLM/ext.hpp"

// program
#include "Macro.h"

// TODO: Scale Implementation

namespace CookieEng
{
namespace Attribute
{
	/*! @class Transform
	*	@brief A Transform Attribute
	*
	*	Tracks a position / rotation and scale in 3D space using the GLM library
	*/
	class Transform
	{
	public:
		/** @brief Transform Ctor
		*
		*	Creates a transform at the world 0, 0, 0 with default rotation and scale
		*/
		Transform();
		/** @brief Transform Dtor
		*
		*	Deletes a transform
		*/
		~Transform() { }

		/** @brief Sets the Model Matrix
		*
		*	Calculates the new Model Matrix from the internal Vec3 attributes
		*/
		void setModelMatrix();

		/** @brief Gets the model matrix
		*	@return The model matrix
		*
		*	Returns the model matrix of the transform
		*/
		inline glm::mat4 getMatrix() { return m_modelMatrix; }

		// position
		// get
		/** @brief Gets the Position 
		*	@return The position vector in 3D
		*
		*	Returns the position vector
		*/
		inline glm::vec3 getPositionVec3() { return m_position; }
		// modify
		/** @brief Sets the absolute position
		*	@param _position The new position
		*
		*	Sets the new position of the transform, disregarding its old position
		*/
		void setPosition(const glm::vec3 &_position);
		/** @brief Moves the transform to a new position relative to its old position
		*	@param _position The difference in position to apply
		*
		*	Translates the position of the transform by the given vector 3D.
		*/
		void translate(const glm::vec3 &_position);

		// rotation
		// modify
		/** @brief Sets the absolute rotation
		*	@param	_rotation	The new rotation
		*	@param	_axis		The axis to rotate on
		*
		*	Sets the new rotation of the transform, disregarding its old rotation
		*/
		void setRotation(const float _rotation, const glm::vec3 &_axis);
		/** @brief Rotates the transform to a new rotation relative to its old rotation
		*	@param	_rotation	The difference in rotation to apply
		*	@param	_axis		The axis to rotate on
		*
		*	Changes the rotation of the transform by the given vector 3D.
		*/
		void rotate(const float _rotation, const glm::vec3 _axis);

	protected:
		glm::vec3	m_position;				/**< The current position */
		glm::vec3	m_rotation;				/**< The current rotation */

		glm::mat4	m_modelMatrix;			/**< The model matrix */
		glm::mat4	m_modelMatrixNS;		/**< The model matrix without scale */

		glm::mat4	m_translationMatrix;	/**< The translation matrix */
		glm::mat4	m_rotationMatrix;		/**< The rotation matrix */
		glm::mat4	m_scaleMatrix;			/**< The scale matrix */
	};
}
}