#pragma once

// cstdlib

// external libs
#include "SDL/SDL.h"

// program
#include "Macro.h"

namespace CookieEng
{
namespace Input
{
namespace Keyboard
{

#ifdef USE_SDL
	enum CNG_Keycode
	{
		CNG_KEY_W = SDLK_w, CNG_KEY_S = SDLK_s, CNG_KEY_A = SDLK_a, CNG_KEY_D = SDLK_d
	};
#endif

	/*! @class Key
	*	@brief Contains a key's state
	*
	*	Contains the current state of a key with its corresponding code for the engine and in SDL
	*/
	class Key
	{
	public:
		/** @brief Key Ctor
		*
		*	Does Nothing
		*/
		Key() {}
		/** @brief Camera Ctor
		*	@param _cngKey The Engine Keycode
		*	@param _sdlKey The SDL Keycode
		*
		*	Creates a key and assigned the keycodes
		*/
		Key(CNG_Keycode _cngKey, SDL_Keycode _sdlKey) : m_CNG_keycode(_cngKey), m_SDL_Keycode(_sdlKey) { }

		/** @brief Returns the keydown state
		*	@return The state the key is in
		*
		*	Returns wether a key is down or not
		*/
		bool isKeyDown() { return m_isDown; }
		/** @brief Sets the keydown state
		*	@param _state The state to set
		*
		*	Sets wether a key is down or not. This is updated by the Keyboard Update or can be done manually to simulate a keypress.
		*/
		void setKeyDown(bool _state) { m_isDown = _state; }

		/** @brief Sets the SDL keycode of a key
		*	@return The SDL Keycode
		*o
		*	Sets wether a key is down or not. This is updated by the Keyboard Update or can be done manually to simulate a keypress.
		*/
		inline SDL_Keycode getSDLKeycode() { return m_SDL_Keycode; }

	protected:
		CNG_Keycode		m_CNG_keycode;			/**< The Engine Keycode */
		SDL_Keycode		m_SDL_Keycode;			/**< The SDL Keycode */
		bool			m_isDown = false;		/**< The key up/down state */
	};
}
}
}
