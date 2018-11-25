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
	/*! @class AudioSource
	*	@brief An audio source
	*
	*	A source of audio for playing sounds
	*/
	class AudioSource
	{
	public:
		/** @brief AudioSource Ctor
		*
		*	Does nothing
		*/
		AudioSource();

		/** @brief Plays the assigned sound effect
		*
		*	Plays the attached sound effect resource
		*/
		void play();

		/** @brief Plays the assigned sound effect
		*	@param _string The resource string to load from
		*
		*	Assigns the sound effect to this source
		*/
		void assign(std::string _string);

	protected:
		std::weak_ptr<Resources::SoundEffect> m_soundEffect;	/**< The sound effect resource */
	};
}
}