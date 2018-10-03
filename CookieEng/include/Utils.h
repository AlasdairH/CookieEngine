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

	/*! @class UtilsStr
	*	@brief String Utilities
	*
	*	Various additional methods for parsing strings
	*/
	class UtilsStr
	{
	public:

		/** @brief Splits a string based on a delimiter
		*	@param _s The string to split
		*	@param _delimiter The character delimiter to split the string around
		*	@return An vector of individual strings
		*
		*	Loads a text file into an std::string.
		*/
		static std::vector<std::string> split(const std::string &_s, char _delimiter)
		{
			std::vector<std::string> tokens;
			std::string token;
			std::istringstream tokenStream(_s);
			while (std::getline(tokenStream, token, _delimiter))
			{
				tokens.push_back(token);
			}
			return tokens;
		}
	};

}
}