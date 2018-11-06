#pragma once

// cstdlib
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

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

	class UtilsFloat
	{
	public:
		/** @brief Returns a random float between the specified range
		*	@param _low The low of the range
		*	@param _high The high of the range
		*	@return A random float inbetween _low and _high
		*
		*	Takes in a low and a high float then gets a random float between the two.
		*/
		static float randFloat(const float _low, const float _high)
		{
			return _low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (_high - _low)));
		}
	};

}
}