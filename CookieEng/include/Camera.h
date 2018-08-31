#pragma once

// cstdlib


// external libs
#include "GLM/glm.hpp"
#include "GLM/ext.hpp"

// program
#include "Macro.h"
#include "Transform.h"

// TODO: Matrix Optimisation

namespace CookieEng
{
namespace Object
{
	/*! @class Camera
	*	@brief Contains the data for the representation of a perspective camera
	*
	*	Contains the data required to represent a camera in OpenGL. This uses the glm::perspective function to create a camera that can be moved around using the
	*	transform.
	*/
	class Camera
	{
	public:
		/** @brief Camera Ctor
		*
		*	Creates a camera at the world 0, 0, 0 with a standard FoV
		*/
		Camera();
		/** @brief Camera Dtor
		*
		*	Deletes the camera
		*/
		~Camera() { }

		Attribute::Transform transform;		/**< The transform attribute of the Camera, used for moving it around the world */

		/** @brief Sets the Field of View
		*	@param _fov The desired Field of View
		*
		*	Sets the FoV and cleans the projection matrix
		*/
		inline void setFOV(const float _fov) { m_fov = _fov; cleanProjectionMatrix(); }
		/** @brief Sets the Aspect Ratio ( width / height )
		*	@param _fov The desired Aspect Ratio
		*
		*	Sets the Aspect Ratio and cleans the projection matrix
		*/
		inline void setAspectRatio(const float _aspect) { m_aspect = _aspect; cleanProjectionMatrix(); }

		/** @brief Return the Projection Matrix
		*	@return The Projection Matrix
		*
		*	Returns the Projection Matrix
		*/
		inline glm::mat4 getProjectionMatrix() { return m_projectionMatrix; }

	protected:
		/** @brief Sets the updated Projection Matrix
		*
		*	Sets a fresh perspective matrix from the FoV, aspect ratio and near / far planes
		*/
		void cleanProjectionMatrix() { m_projectionMatrix = glm::perspective(m_fov, m_aspect, 0.1f, 100.0f); }
		
		float		m_fov;					/**< The current FoV */
		float		m_aspect;				/**< The current Aspect Ratio */

		glm::mat4	m_projectionMatrix;		/**< The Projection Matrix */
	};
}
}