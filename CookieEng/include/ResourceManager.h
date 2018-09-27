#pragma once

// cstdlib
#include <memory>
#include <map>
#include <string>

// external libs

// program
#include "Macro.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Material.h"



namespace CookieEng
{
namespace Core
{
	// Material forward decleration
	class Material;

	/*! @class ResourceManager
	*	@brief A Singleton for handling the storage of resources
	*
	*	This class handles the storage of resources for use by elements of the game engine. This allows the same Texture, ShaderProgram, etc to
	*	be used by multiple entities or services. The resources are stored in a map and access is checked before operations on the stored resources is allowed.
	*	This class may need a bit of refactoring, seems like I'm writing a lot of semi-duplicate code.
	*/
	class ResourceManager
	{
	public:
		/** @brief Gets the static instance of the ResourceManager
		*
		*	Gets the static instance of the ResourceManager.
		*/
		static ResourceManager& getInstance()
		{
			static ResourceManager instance;	// Guaranteed to be destroyed.
												// Instantiated on first use.
			return instance;
		}

		// TODO: Add more!
		// -------------------------------------------------------------------- TEXTURE --------------------------------------------------------------------
		/** @brief Loads a texture to the resource manager
		*	@param _filepath The path to the Image File to be loaded
		*	@param _name The unique name to give the texture
		*
		*	Uses the image loader to load a texture and save it to the ResourceManager.
		*/
		void loadTexture(const std::string _filepath, const std::string _name);
		/** @brief Remove a texture from the Resource Manager
		*	@param _name The texture to remove
		*
		*	Unloads and removes a texture from the Resource Manager
		*/
		void removeTexture(const std::string _name);
		/** @brief Provides a shared pointer to the requested Texture.
		*	@param _name The name of the Resource requested
		*
		*	Grabs the Texture from the map using the name as the key and returns a shared_ptr to the resource.
		*/
		std::shared_ptr<Graphics::Texture> getTexture(std::string _name);
		/** @brief Returns true if the resource exists in the Resource Manager
		*	@param _name The name of the resource
		*
		*	Returns true if the resource exists in the Resource Manager, false otherwise.
		*/
		bool textureExists(const std::string _name);

		// -------------------------------------------------------------------- SHADER PROGRAM --------------------------------------------------------------------
		/** @brief Loads a ShaderProgram to the resource manager
		*	@param _filepathVert The path to the GLSL Vertex Shader File to be loaded
		*	@param _filepathFrag The path to the GLSL Fragment Shader File to be loaded
		*	@param _name The unique name to give the ShaderProgram
		*
		*	Loads a shader to the ResourceManager, verifying its compile status.
		*/
		void loadShaderProgram(const std::string _filepathVert, const std::string _filepathFrag, const std::string _name);
		/** @brief Remove a Shader Program from the Resource Manager
		*	@param _name The ShaderProgram to remove
		*
		*	Unloads and removes a Shader Program from the Resource Manager
		*/
		void removeShaderProgram(const std::string _name);
		/** @brief Provides a shared pointer to the requested ShaderProgram.
		*	@param _name The name of the Resource requested
		*
		*	Grabs the ShaderProgram from the map using the name as the key and returns a shared_ptr to the resource.
		*/
		std::shared_ptr<Graphics::ShaderProgram> getShaderProgram(std::string _name);
		/** @brief Returns true if the resource exists in the Resource Manager
		*	@param _name The name of the resource
		*
		*	Returns true if the resource exists in the Resource Manager, false otherwise.
		*/
		bool shaderExists(const std::string _name);

		// -------------------------------------------------------------------- MATERIAL --------------------------------------------------------------------
		/** @brief Loads a Material to the resource manager
		*	@param _shaderProgram the shader to assign to the material
		*	@param _name The unique name to give the Material
		*
		*	Creates a Material on the ResourceManager.
		*/
		void createMaterial(const std::string _shaderProgram, const std::string _name);
		/** @brief Remove a Material from the Resource Manager
		*	@param _name The Material to remove
		*
		*	Unloads and removes a Material from the Resource Manager
		*/
		void removeMaterial(const std::string _name);
		/** @brief Provides a shared pointer to the requested Material.
		*	@param _name The name of the Resource requested
		*
		*	Grabs the Material from the map using the name as the key and returns a shared_ptr to the resource.
		*/
		std::shared_ptr<Core::Material> getMaterial(std::string _name);
		/** @brief Returns true if the resource exists in the Resource Manager
		*	@param _name The name of the resource
		*
		*	Returns true if the resource exists in the Resource Manager, false otherwise.
		*/
		bool materialExists(const std::string _name);


		// ------------------------------------------------
		ResourceManager(ResourceManager const&)		= delete;
		void operator=(ResourceManager const&)		= delete;

	protected:
		/** @brief ResourceManager Ctor
		*
		*	This is called on the first time the ResourceManager instance is grabbed.
		*/
		ResourceManager();
		~ResourceManager();

		std::map<std::string, std::shared_ptr<Graphics::Texture>>			m_textureMap;			/**< The Std::Map of Textures that can be loaded */
		std::map<std::string, std::shared_ptr<Graphics::ShaderProgram>>		m_shaderProgramMap;		/**< The Std::Map of Shader Programs that can be loaded */
		std::map<std::string, std::shared_ptr<Core::Material>>				m_materialMap;			/**< The Std::Map of Shader Programs that can be loaded */
	};
}
}
