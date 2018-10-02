#pragma once

// cstdlib
#include <string>

// external libs

// program
#include "ServiceLocator.h"

namespace CookieEng
{
namespace Resource
{
	enum ResourceType { RESOURCE_DEFAULT, RESOURCE_SHADER, RESOURCE_TEXTURE, RESOURCE_MATERIAL };

	class Resource
	{
	public:
		virtual void load(const std::string &_name, const std::string &_filepath) { }
		virtual void unload() { };

		virtual bool isLoaded() { return m_isLoaded; }

		inline void setName(const std::string &_name) { m_name = _name; }
		inline void setResourceID(const unsigned int &_resourceID) { m_resourceID = _resourceID; }
		inline void setFilepath(const std::string &_filepath) { m_filepath = _filepath; }


	protected:
		ResourceType m_resourceType;

		std::string m_name;
		unsigned int m_resourceID;


		std::string m_filepath;

		bool m_isLoaded;
	};
}
}