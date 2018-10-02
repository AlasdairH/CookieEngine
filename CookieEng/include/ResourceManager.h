#pragma once

// cstdlib
#include <memory>
#include <string>
#include <unordered_map>

// external libs

// program
#include "Macro.h"
#include "Resource.h"

// TODO: Doxygen

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

		template <typename T>
		void load(const std::string &_name, const std::string &_filepath)
		{
			static_assert(std::is_base_of<Resource::Resource, T>::value, "T must inherit from Resource");

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

		template<typename T>
		std::shared_ptr<T> get(std::string _name)
		{ 
			return std::dynamic_pointer_cast<T>(m_resources[_name]);
		}

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
		~ResourceManager();

		std::unordered_map<std::string, std::shared_ptr<Resource::Resource>> m_resources;
	};
}
}
