#include "ServiceContainer.h"

namespace CookieEng
{
namespace Services
{

	ServiceContainer::ServiceContainer()
	{
		m_svsInitialiser = nullptr;
		m_svsFileManager = nullptr;
		m_svsMessageQueue = nullptr;
	}

	ServiceContainer::~ServiceContainer()
	{
		Services::ServiceLocator::clearInitialiser();
		Services::ServiceLocator::clearFileManager();
		Services::ServiceLocator::clearMessageQueue();
		delete m_svsInitialiser;
		delete m_svsFileManager;
		delete m_svsMessageQueue;
	}

	void ServiceContainer::assignServices()
	{
		m_svsInitialiser = new Services::Initialiser();
		Services::ServiceLocator::setInitialiser(m_svsInitialiser);
		m_svsFileManager = new Services::FileManager();
		Services::ServiceLocator::setFileManager(m_svsFileManager);
		m_svsMessageQueue = new Services::MessageQueue();
		Services::ServiceLocator::setMessageQueue(m_svsMessageQueue);
	}

}
}