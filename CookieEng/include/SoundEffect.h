#pragma once

// cstdlib
#include <string>

// external libs
#include "SDL_Mixer/SDL_mixer.h"

// program
#include "Macro.h"
#include "Resource.h"

namespace CookieEng
{
	namespace Resources
	{
		/*! @class SoundEffect
		*	@brief A sound effect that can be played through an AudioSource
		*
		*	A sound effect can be loaded and assigned to an AudioSource to be played to an AudioListener
		*/
		class SoundEffect : public Resource
		{
		public:
			/** @brief SoundEffect Ctor
			*
			*	Instantiates a sound effect but does not load a sound
			*/
			SoundEffect();
			/** @brief SoundEffect Ctor
			*	@param _name The name to give the SoundEffect resource
			*	@param _filepath The path to the image to be loaded
			*
			*	Instantiates a sound effect and loads the sound from a file
			*/
			SoundEffect(const std::string &_name, const std::string &_filepath);
			/** @brief SoundEffect Dtor
			*
			*	Frees the sound effect
			*/
			~SoundEffect();

			/** @brief Load Sound Effect
			*	@param _name The name to assign the loaded resource
			*	@param _filepath The path to the .wav to be loaded
			*
			*	Loads a .wav file to a sound chunk
			*/
			void load(const std::string &_name, const std::string &_filepath) override;

			/** @brief Plays sound effect
			*
			*	Plays the sound effect
			*/
			void play();

		protected:
			Mix_Chunk	*m_sound			= NULL;
		};
	}
}