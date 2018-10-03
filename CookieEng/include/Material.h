#pragma once

// cstdlib
#include <memory>

// external libs
#include "GLM/glm.hpp"

// program
#include "ResourceManager.h"
#include "ShaderProgram.h"
#include "Texture.h"

// Add Specular etc



namespace CookieEng
{
namespace Resources
{
	// Resource Manager forward decleration
	class ResourceManager;

	/*! @class Material
	*	@brief A material that can be used for rendering
	*
	*	Abstracts a shader to allow for different materials to use the same shader. This class will hold (TODO: Uniform Buffer) uniform
	*	settings that will be applied when the material us used.
	*/
	class Material : public Resource
	{
	public:
		/** @brief Material Ctor
		*
		*	Does Nothing
		*/
		Material() { }
		/** @brief Material Dtor
		*
		*	Does Nothing
		*/
		~Material() { }

		/** @brief Uses the Material (Binds)
		*
		*	Binds the shader and texture members.
		*/
		void use() const;
		/** @brief Stops Using the Material (Unbinds)
		*
		*	Unbinds the shader and texture members.
		*/
		void unUse() const;

		/** @brief Sets the Material's Shader
		*	@param _resMgr_shaderName The name (in the resource mananger) of the shader that is to be used 
		*
		*	Sets the Material's shader that will be used when rendering.
		*/
		void setShader(const std::string _resMgr_shaderName);

		/** @brief Sets the Material's Diffuse Colour to a Texture
		*	@param _resMgr_textureName The name (in the resource mananger) of the texture that is to be used
		*
		*	Sets the Material's Texture that will be used when rendering the diffuse of the object this Material is assigned to.
		*/
		void setDiffuse(const std::string _resMgr_textureName);
		/** @brief Sets the Material's Diffuse Colour to a solid colour
		*	@param _colour The solid colour to use in normalised RGBA.
		*
		*	Sets the Material's Diffuse colour that will be used when rendering the diffuse of the object this Material is assigned to.
		*/
		void setDiffuse(const glm::vec4 &_colour);

		/** @brief Sets the Materials MVP uniforms | TODO: Uniform Buffer Implementation
		*	@param _m The model matrix
		*	@param _v The view matrix
		*	@param _p The projection matrix
		*
		*	Sets the MVP to be calculated in the shader. This is kept seperate because individual elements are required for lighting.
		*/
		void setMVP(const glm::mat4 &_m, const glm::mat4 &_v, const glm::mat4 &_p);

	protected:
		std::shared_ptr<ShaderProgram>	m_shaderProgram;		/**< The Material's Shader */
		std::shared_ptr<Texture>					m_textureDiffuse;		/**< The Material's Diffuse Texture (if used) */
		glm::vec4									m_diffuseColour;		/**< The Material's Diffuse Colour (if used) */
	};
}
}