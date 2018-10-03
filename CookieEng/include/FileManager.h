#pragma once

// cstdlib
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

// external libs

// program
#include "Macro.h"
#include "Utils.h"

namespace CookieEng
{
namespace Services
{
	/*! @class FileManager
	*	@brief A Manager Class that handles the loading of files either synchronously or asynchronously.
	*
	*	This class uses the stdlib to load files into the engine. This could be for text files, shaders, images
	*	or models.
	*/
	class FileManager
	{
	public:
		/** @brief The FileManager Constructor
		*
		*	Sets up the File Manager
		*/
		FileManager();

		/** @brief The FileManager Destructor
		*
		*	Closes the File Manager
		*/
		~FileManager();

		/** @brief Synchronous loading of text files.
		*	@param _filepath The path to the Text File to be loaded
		*	@return An std::string containing the contents of the text file.
		*
		*	Loads a text file into an std::string.
		*/
		std::string loadTextFile(std::string _filepath);

		/** @brief Asynchronous loading of text files.
		*	@param _filepath The path to the Text File to be loaded
		*	@return An std::string containing the contents of the text file.
		*
		*	Loads a text file into an std::string.
		*/
		std::string loadTextFileASync(std::string _filepath) { } 

	protected:

	};

}
}