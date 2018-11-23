#include "SoundEffect.h"

namespace CookieEng
{
namespace Resources
{
	SoundEffect::SoundEffect()
	{

	}

	SoundEffect::SoundEffect(const std::string & _name, const std::string & _filepath)
	{
		m_filepath = _filepath;
	}

	SoundEffect::~SoundEffect()
	{
		Mix_FreeChunk(m_sound);
	}

	void SoundEffect::load(const std::string & _name, const std::string & _filepath)
	{
		m_sound = Mix_LoadWAV(_filepath.c_str());
		if (m_sound == NULL)
		{
			LOG_WARNING("Error loading sound: " << _filepath);
			return;
		}
		else
		{
			LOG_MESSAGE("Loaded sound " << _filepath);
		}
	}
	void SoundEffect::play()
	{
		if (m_sound == NULL)
		{
			LOG_WARNING("Error playing sound " << m_filepath << ", not valid");
			return;
		}
		Mix_PlayChannel(-1, m_sound, 0);
	}
}
}