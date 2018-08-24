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
#include "Mesh.h"



namespace CookieEng
{
namespace Services
{
	// TODO: Move this
	struct ObjVertex
	{
		int f;
		int vt;
		int vn;
	};

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

		/** @brief Loads a .obj file to a Mesh
		*	@param _filepath The path to the .Obj to be loaded
		*	@return A mesh containing the vertex and index data from the .obj file
		*
		*	WARNING: ALL LOADED MESHES MUST BE TRIANGULATED
		*	Uses the loadTextFile method to load the .obj as a string and then parses the file for the different attributes for storing in a mesh.
		*	This could definietly be more efficient but it's completely written by me and thats how I like it!
		*/
		Data::Mesh loadMesh(const std::string _filepath);

		// TODO: Implement
		/** @brief Loads an Image
		*	@param _filepath The path to the Image to be loaded
		*	@return The loaded image
		*
		*	
		*/
		Data::Mesh loadImage(const std::string _filepath) { }

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

	protected:

	};

}
}