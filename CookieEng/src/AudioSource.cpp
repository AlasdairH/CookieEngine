#include "AudioSource.h"

namespace CookieEng
{
namespace Audio
{
	AudioSource::AudioSource()
	{

	}

	void AudioSource::play()
	{
		if (!m_soundEffect.expired())
		{
			m_soundEffect.lock()->play();
		}
	}

	void AudioSource::assign(std::string _resourceName)
	{
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();
		m_soundEffect = resourceManager.get<Resources::SoundEffect>(_resourceName);
	}
}
}