#pragma once

// cstdlib
#include <memory>
#include <map>
#include <string>

// external libs

// program
#include "Macro.h"
#include "Resource.h"



namespace CookieEng
{
namespace ResMgmt
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

		template<typename T>
		std::shared_ptr<T> getResource(std::string _name)
		{

		}
		

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

		std::map<std::string, std::shared_ptr<Resource>> m_resources;
	};
}
}
