#pragma once

// cstdlib
#include <vector>
#include <string>
#include <sstream>

// external libs

// program

namespace CookieEng
{
namespace Utilities
{

	class UtilsStr
	{
	public:
		static std::vector<std::string> split(const std::string& s, char delimiter)
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