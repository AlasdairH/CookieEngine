#include "ServiceLocator.h"

namespace CookieEng
{
namespace Services
{
	Initialiser* ServiceLocator::s_initialiser = nullptr;
	FileManager* ServiceLocator::s_fileManager = nullptr;


	// ------------------------ INITIALISER ------------------------
	Initialiser& ServiceLocator::getInitialiser()
	{
		if (s_initialiser == nullptr)
		{
			std::cout << "WARNING: Service (Initialiser) set to NULLPTR" << std::endl;
			return *s_initialiser;
		}
		// return reference to the initialiser
		return *s_initialiser;
	}

	void ServiceLocator::setInitialiser(Initialiser* _initialiser)
	{
		// if the initialiser being set is null
		if (_initialiser == nullptr)
		{
			std::cout << "ERROR: Initialiser NULL" << std::endl;
		}
		// if it is a valid initialiser
		else
		{
			s_initialiser = _initialiser;
		}
	}

	// ------------------------ FILE MANAGER ------------------------
	FileManager& ServiceLocator::getFileManager()
	{
		if (s_fileManager == nullptr)
		{
			std::cout << "WARNING: Service (FileManager) set to NULLPTR" << std::endl;
			return *s_fileManager;
		}
		// return reference to the initialiser
		return *s_fileManager;
	}

	void ServiceLocator::setFileManager(FileManager* _fileManager)
	{
		// if the initialiser being set is null
		if (_fileManager == nullptr)
		{
			std::cout << "ERROR: Initialiser NULL" << std::endl;
		}
		// if it is a valid initialiser
		else
		{
			s_fileManager = _fileManager;
		}
	}
}
}