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
	class ShaderProgram
	{
	public:
		/** @brief Program Ctor
		*
		*	Creates a shader program and sets the verified status to false.
		*/
		ShaderProgram();

		/** @brief Program Ctor
		*	@param _vertShaderPath The path to the Vertex Shader file
		*	@param _fragShaderPath The path to the Fragment Shader file
		*
		*	Creates a shader program and adds a vertex + fragment shader
		*/
		ShaderProgram(const std::string &_vertShaderPath, const std::string &_fragShaderPath);

		/** @brief Program Ctor
		*
		*	Deletes the shader program and frees the GPU memory
		*/
		~ShaderProgram() { glDeleteProgram(m_programID); LOG_MESSAGE("Deleted Program: " << m_programID); }

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

		/** @brief Gets the location of the specified Uniform in a shader
		*	@param _name The uniform to retrive
		*	@return The uniform location
		*
		*	Gets the location of a uniform in a shader based on its name. If the shader uniform location has not been
		*	requested before, it is cached so that future requests do not incur an OpenGL call.
		*/
		int getUniformLocation(const std::string &_name);

		/** @brief Sets a single float uniform
		*	@param _name The name of the uniform to modify
		*	@param _value The value to set the uniform to
		*
		*	Uses the getUniformLocation method to get the uniform location and set it to the given value.
		*/
		void setUniform1f(const std::string &_name, float _value);

		/** @brief Sets a vec3 uniform
		*	@param _name The name of the uniform to modify
		*	@param _value1 The x value of the Vec4
		*	@param _value2 The y value of the Vec4
		*	@param _value3 The z value of the Vec4
		*
		*	Uses the getUniformLocation method to get the uniform location and set it to the given values.
		*/
		void setUniform3f(const std::string &_name, float _value1, float _value2, float _value3);

		/** @brief Sets a vec4 uniform
		*	@param _name The name of the uniform to modify
		*	@param _value1 The x value of the Vec4
		*	@param _value2 The y value of the Vec4
		*	@param _value3 The z value of the Vec4
		*	@param _value4 The w value of the Vec4
		*
		*	Uses the getUniformLocation method to get the uniform location and set it to the given values.
		*/
		void setUniform4f(const std::string &_name, float _value1, float _value2, float _value3, float _value4);

		/** @brief Sets a single integar uniform
		*	@param _name The name of the uniform to modify
		*	@param _value The value to set the uniform to
		*
		*	Uses the getUniformLocation method to get the uniform location and set it to the given value.
		*/
		void setUniform1i(const std::string &_name, int _value);

		/** @brief Sets a matrix(4x4) uniform
		*	@param _name The name of the uniform to modify
		*	@param _value The value to set the uniform to
		*
		*	Uses the getUniformLocation method to get the uniform location and set it to the given value.
		*/
		void setUniformMat4f(const std::string &_name, const glm::mat4 &_value);


	protected:

		GLuint m_programID;		/**< The OpenGL ID */

		bool m_verified;		/**< Flag for the shaders verified status */

		std::unordered_map<std::string, int> m_uniformLocationCache;	/**< The cache of uniform names to locations */
	};

}
}