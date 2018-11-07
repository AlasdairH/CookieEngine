#pragma once

// cstdlib
#include <string>
#include <unordered_map>

// external libs

// program
#include "InputKey.h"

namespace CookieEng
{
namespace Input
{
namespace Keyboard
{
	/*! @class Keyboard
	*	@brief A keyboard class that handles the state of various keys
	*
	*	This keyboard class contains the data for keys on a keyboard. Keys can be added and linked to the SDL input.
	*/
	class Keyboard
	{
	public:
		/** @brief Camera Ctor
		*
		*	Does nothing
		*/
		Keyboard();

		/** @brief Adds a CNG_Keycode and links it to a SDL_Keycode.
		*	@param _cngKey The Cookie Engine CNG_keycode that represents a key
		*	@param _sdlKey The SDL_Keycode to link to
		*
		*	Adds a key to the keyboard and links the SDL keys updates.
		*/
		void addKey(CNG_Keycode _cngKey, SDL_Keycode _sdlKey);

		/** @brief Get up/down key state of the given key
		*	@param _key The key to get the state of
		*
		*	Returns wether a key is up or down. This is set by the keyboard update.
		*/
		bool isKeyDown(CNG_Keycode _key) { return m_keys[_key].isKeyDown(); }

		/** @brief Get up/down key state of the given key
		*	@param incomingEvent The SDL_KeyboardEvent that events are pulled from to update the keyboard
		*
		*	Grabs the events from incomingEvent and updates the keyboard
		*/
		void update(SDL_KeyboardEvent &incomingEvent);

	protected:
		std::unordered_map<SDL_Keycode, Key> m_keys;	/**< The keys to be updated by the keyboard update */
	};
}
}
}
