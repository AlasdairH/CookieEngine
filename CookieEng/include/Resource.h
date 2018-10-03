#pragma once

// cstdlib
#include <string>

// external libs

// program

namespace CookieEng
{
namespace Resources
{
	enum ResourceType { RESOURCE_DEFAULT, RESOURCE_SHADER, RESOURCE_TEXTURE, RESOURCE_MATERIAL, RESOURCE_MESH };	/**< The known resource types */

	/*! @class Resource
	*	@brief A base class for any engine resources (stuff that can be loaded)
	*
	*	A base class for resrouces to inherit from. On resource load, the load() method will be called and each resource should implement
	*	their own method of loading.
	*/
	class Resource
	{
	public:
		/** @brief Asynchronous loading of text files.
		*	@param _name The name to assign the resource
		*	@param _filepath The path to the resource to be loaded from 
		*
		*	This method is called by the resource manager when the resource is loaded. This should be
		*	overridden by each resource as they all most likely require their own loading instructions.
		*/
		virtual void load(const std::string &_name, const std::string &_filepath) { }
		/** @brief Called on the unload of a resource
		*
		*	This method is called when a resource is unloaded. Should be overridden.
		*/
		virtual void unload() { };

		/** @brief Returns the loaded status of a resource
		*
		*	Returns the loaded status of a resource
		*/
		virtual bool isLoaded() { return m_isLoaded; }

		/** @brief Sets the Resource name
		*	@param _name The name to set the resource to
		*
		*	Sets the Resource name
		*/
		inline void setName(const std::string &_name) { m_name = _name; }
		/** @brief Sets the Resource ID
		*	@param _resourceID The ID to set the resource to
		*
		*	Sets the Resource ID
		*/
		inline void setResourceID(const unsigned int &_resourceID) { m_resourceID = _resourceID; }
		/** @brief Sets the Resource filepath
		*	@param _filepath The filepath to set the resource to
		*
		*	Sets the Resource filepath
		*/
		inline void setFilepath(const std::string &_filepath) { m_filepath = _filepath; }


	protected:
		ResourceType	m_resourceType;		/**< The resource type */

		std::string		m_name;				/**< The resource name */
		unsigned int	m_resourceID;		/**< The resource ID */

		std::string		m_filepath;			/**< The resource filepath */

		bool			m_isLoaded;			/**< Flag for the loaded state of the resource */
	};
}
}