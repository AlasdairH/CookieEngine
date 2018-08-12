#include "ServiceContainer.h"

namespace CookieEng
{
namespace Services
{

	ServiceContainer::ServiceContainer()
	{
		m_svsInitialiser = nullptr;
		m_svsFileManager = nullptr;
	}

	ServiceContainer::~ServiceContainer()
	{
		Services::ServiceLocator::clearInitialiser();
		Services::ServiceLocator::clearFileManager();
		delete m_svsInitialiser;
		delete m_svsFileManager;
	}

	void ServiceContainer::assignServices()
	{
		m_svsInitialiser = new Services::Initialiser();
		Services::ServiceLocator::setInitialiser(m_svsInitialiser);
		m_svsFileManager = new Services::FileManager();
		Services::ServiceLocator::setFileManager(m_svsFileManager);
	}

}
}