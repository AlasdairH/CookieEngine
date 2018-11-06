#pragma once

// cstdlib
#include <memory>
#include <string>
#include <unordered_map>
#include <assert.h>

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

		/** @brief Loads a resource to the manager
		*	@param T The type to load
		*	@param _name The name to assign the loaded resource
		*	@param _filepath The filepath to the resource file
		*
		*	Takes the template of the resource to load and checks it is first a derived class of Resource.
		*	The method then loads the resource to the manager with the name and path specified.
		*/
		template <typename T>
		void load(const std::string &_name, const std::string &_filepath)
		{
			// assert the resource is a derivative of Resource
			static_assert(std::is_base_of<Resources::Resource, T>::value, "T must inherit from Resource");

			// if the resource already exists
			if(exists(_name))
			{ 
				LOG_ERROR("Unable to add resource " << _name << " to ResourceManager, it already exists");
				return;
			}

			m_resources[_name] = std::make_shared<T>();
			m_resources[_name]->setName(_name);
			m_resources[_name]->setFilepath(_filepath);
			m_resources[_name]->load(_name, _filepath);
		}

		/** @brief gets a shared pointer to the requested resource
		*	@param T The type to get
		*	@param _name The name of the resource
		*	@return A shared pointer to the requested resource
		*
		*	Takes a resource type through a template and a name argument. The method then casts the resource from the map member to the desired
		*	type and returns it as a shared pointer.
		*/
		template<typename T>
		std::shared_ptr<T> get(std::string _name)
		{
			if (exists(_name))
			{
				return std::dynamic_pointer_cast<T>(m_resources[_name]);
			}
			else
			{
				LOG_ERROR("Requested Resource " << _name << " does not exist");
				assert(exists(_name));
				return std::dynamic_pointer_cast<T>(m_resources[_name]);
			}
		}

		/** @brief Tests to see if the resource map contains a key
		*	@param _name The key to test
		*	@return True if it exists in the map, false otherwise
		*
		*	Attempts to find the given key in the map and returns the resulting boolean
		*/
		bool exists(const std::string &_name);
		

		// ------------------------------------------------
		ResourceManager(ResourceManager const&)		= delete;
		void operator=(ResourceManager const&)		= delete;

	protected:
		/** @brief ResourceManager Ctor
		*
		*	This is called on the first time the ResourceManager instance is grabbed.
		*/
		ResourceManager();
		/** @brief ResourceManager Dtor
		*
		*	Called on program close
		*/
		~ResourceManager();

		std::unordered_map<std::string, std::shared_ptr<Resources::Resource>> m_resources;	/**< The resource map containing the base Resource class */
	};
}
}
