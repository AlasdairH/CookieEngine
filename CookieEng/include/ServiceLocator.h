#pragma once

// cstdlib
#include <iostream>

// external libs

// program
#include "Initialiser.h"
#include "FileManager.h"

namespace CookieEng
{
namespace Services
{
	/*! @class ServiceLocator
	*	@brief Works as an interface to the managers and services provided by the engine
	*
	*	This class provides access to services and managers. These are static to follow a
	*	singleton pattern that can be accessed anywhere in the engine.
	*	
	*	Different managers and services can be applied to the locator to make multiple versions of
	*	the same manager possible if differing settings were required.
	*	
	*/
	class ServiceLocator
	{
	public:
		//------------------------------------------------------------------
		/** @brief Returns a reference to the initialiser
		*	@return The Initialiser
		*
		*	Returns a reference to the initialiser.
		*/
		static Initialiser& getInitialiser();
		/** @brief Sets the Initialiser
		*	@param _initialiser The initialiser to be used by the Service Locator
		*
		*	Sets the initialiser that will be accessesd through the Service Locator
		*/
		static void setInitialiser(Initialiser* _initialiser);
		/** @brief Clears the Initialiser
		*
		*	Sets the Initialiser to a nullptr
		*/
		inline static void clearInitialiser() { s_initialiser = nullptr; }
		//------------------------------------------------------------------
		/** @brief Returns a reference to the File Manager
		*	@return The File Manager
		*
		*	Returns a reference to the File Manager
		*/
		static FileManager& getFileManager();
		/** @brief Sets the FileManager
		*	@param _fileManager The File Manager to be used by the Service Locator
		*
		*	Sets the FileManager that will be accessesd through the Service Locator
		*/
		static void setFileManager(FileManager* _fileManager);
		/** @brief Clears the FileManager
		*
		*	Sets the File Manager to a nullptr
		*/
		inline static void clearFileManager() { s_fileManager = nullptr; }

	protected:
		static Initialiser* s_initialiser;	/**< Static Pointer to the Initialiser. */
		static FileManager* s_fileManager;	/**< Static Pointer to the File Mananger. */
	};

}
}