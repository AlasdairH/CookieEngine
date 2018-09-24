#pragma once

// cstdlib
#include <memory>
#include <string>

// external libs

// program
#include "Macro.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"

namespace CookieEng
{
namespace Core
{
	class ResourceLoader
	{
	public:
		/** @brief Gets the static instance of the ResourceLoader
		*
		*	Gets the static instance of the ResourceLoader.
		*/
		static ResourceLoader& getInstance()
		{
			static ResourceLoader instance;	// Guaranteed to be destroyed.
												// Instantiated on first use.
			return instance;
		}

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

		// TODO: Move this
		std::vector<std::string> split(const std::string& s, char delimiter)
		{
			std::vector<std::string> tokens;
			std::string token;
			std::istringstream tokenStream(s);
			while (std::getline(tokenStream, token, delimiter))
			{
				tokens.push_back(token);
			}
			return tokens;
		}
	};
}
}
