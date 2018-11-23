#pragma once

// cstdlib
#include <string>
#include <memory>

// external libs


// program
#include "Macro.h"
#include "SoundEffect.h"
#include "ResourceManager.h"

namespace CookieEng
{
namespace Audio
{
	class AudioSource
	{
	public:
		AudioSource();

		void play();
		void assign(std::string _string);

	protected:
		std::weak_ptr<Resources::SoundEffect> m_soundEffect;
	};
}
}