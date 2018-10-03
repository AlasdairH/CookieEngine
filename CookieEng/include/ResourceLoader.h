#pragma once

// cstdlib
#include <memory>
#include <string>

// external libs

// program
#include "Macro.h"
#include "Utils.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"

#include "Texture.h"
#include "Material.h"
#include "ShaderProgram.h"

namespace CookieEng
{
namespace Core
{
	/*! @class ResourceLoader
	*	@brief Loads a list of resources from a .lvl file
	*
	*	Takes a .lvl file and parses it for the loading of resources to the ResourceManager singleton.
	*/
	class ResourceLoader
	{
	public:
		/** @brief Gets the static instance of the ResourceLoader
		*
		*	Gets the static instance of the ResourceLoader.
		*/
		static ResourceLoader& getInstance()
		{
			static ResourceLoader instance;		// Guaranteed to be destroyed.
												// Instantiated on first use.
			return instance;
		}

		/** @brief Loads a .lvl file for resource loading
		*	@param _filepath The filepath to load from
		*
		*	This loads a file (.lvl) to get the load instructions from
		*/
		void fromFile(const std::string _filepath);

		// ------------------------------------------------
		ResourceLoader(ResourceLoader const&) = delete;
		void operator=(ResourceLoader const&) = delete;

	protected:
		/** @brief ResourceManager Ctor
		*
		*	This is called on the first time the ResourceManager instance is grabbed.
		*/
		ResourceLoader();
	};
}
}
