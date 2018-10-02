#include "ResourceManager.h"

namespace CookieEng
{
namespace ResMgmt
{

	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{

	}

	bool ResourceManager::exists(const std::string &_name)
	{
		auto found = m_resources.find(_name);
		if (found == m_resources.end())
		{
			return false;
		}
		return true;
	}
}
}
