#pragma once

// cstdlib
#include <iostream>
#include <string>

// external libs

// program
#include "ServiceLocator.h"
#include "Initialiser.h"
#include "FileManager.h"
#include "MessageQueue.h"

namespace CookieEng
{
namespace Services
{
	/*! @class ServiceContainer
	*	@brief The ServiceContainer acts as a container for services that can be located by the ServiceLocator
	*
	*	This class works to allocate pointers to the various services and handle their deletion once the container is shut down.
	*/
	class ServiceContainer
	{
	public:
		/** @brief The Service Container Constructor
		*
		*	Assigns Nullptr to all member pointers.
		*	
		*/
		ServiceContainer();

		/** @brief Adds a light to the scene.
		*
		*	Deletes the service pointers for memory cleanup
		*/
		~ServiceContainer();

		/** @brief Allocates the Services
		*
		*	Allocates services and assigns them to the Service Locator.
		*/
		void assignServices();

	protected:
		Initialiser* m_svsInitialiser;		/**< A pointer to the Initialiser. */
		FileManager* m_svsFileManager;		/**< A pointer to the File Manager. */
		MessageQueue* m_svsMessageQueue;	/**< A pointer to the Message Queue. */
	};

}
}