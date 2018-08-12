#pragma once

// cstdlib
#include <string>
#include <iostream>
#include <vector>

// external libs
#include "GL/glew.h"

// program
#include "ServiceLocator.h"
#include "Shader.h"

namespace CookieEng
{
namespace Graphics
{
	/*! @class Program
	*	@brief Abstracted OpenGL Program
	*
	*	Abstracts and provides simple utilities for an OpenGL Shader Program. The program MUST be verified before it can be bound.
	*/
	class Program
	{
	public:
		/** @brief Program Ctor
		*
		*	Creates a shader program and sets the verified status to false.
		*/
		Program();

		/** @brief Attaches a Shader to the Program
		*	@param _shader The shader to be attached
		*
		*	Attaches a shader to the program.
		*/
		void attachShader(Shader &_shader);

		/** @brief Links the Shader Program
		*
		*	Links the shader program.
		*/
		void link();

		/** @brief Verifys the Shader Program
		*
		*	Verifies the shader program and ensures it can run.
		*/
		bool verify();

		/** @brief Binds the shader
		*
		*	Binds the shader. For this to sucseed, the shader must be verified.
		*/
		void bind() const;
		/** @brief unBinds the shader
		*
		*	unBinds the shader.
		*/
		void unBind() const;


	protected:

		GLuint m_programID;		/**< The OpenGL ID */

		bool m_verified;		/**< Flag for the shaders verified status. */
	};

}
}