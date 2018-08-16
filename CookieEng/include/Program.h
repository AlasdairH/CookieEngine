#pragma once

// cstdlib
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

// external libs
#include "GL/glew.h"
#include "GLM/common.hpp"
#include "GLM/ext.hpp"

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

		// TODO: Doxygen
		int getUniformLocation(const std::string &_name);

		void setUniform1f(const std::string &_name, float _value);
		void setUniform4f(const std::string &_name, float _value1, float _value2, float _value3, float _value4);

		void setUniform1i(const std::string &_name, int _value);

		void setUniformMat4f(const std::string &_name, const glm::mat4 &_value);


	protected:

		GLuint m_programID;		/**< The OpenGL ID */

		bool m_verified;		/**< Flag for the shaders verified status. */

		std::unordered_map<std::string, int> m_uniformLocationCache;
	};

}
}