#pragma once

// cstdlib
#include <memory>
#include <string>

// external libs

// program
#include "Macro.h"
#include "Utils.h"
#include "Keyboard.h"
#include "Gamepad.h"

namespace CookieEng
{
namespace Input
{
	class InputManager
	{
	public:
		/** @brief Gets the static instance of the InputManager
		*
		*	Gets the static instance of the InputManager.
		*/
		static InputManager& getInstance()
		{
			static InputManager instance;		// guaranteed to be destroyed.
												// instantiated on first use.
			return instance;
		}

		/** @brief Updates the contained input devices
		*
		*	Updates the contained input devices
		*/
		void onUpdate(SDL_Event &_event);

		//TODO: Doxygen

		inline bool validController(int _id) { if (_id < m_gamepads.size()) return true; else return false; }

		std::shared_ptr<Controllers::Gamepad> getGamepad(int _id);

		std::shared_ptr<Keyboard::Keyboard> getKeyboard() { return m_keyboard; }

		// ------------------------------------------------
		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

	protected:
		/** @brief InputManager Ctor
		*
		*	This is called on the first time the InputManager instance is grabbed.
		*/
		InputManager();


		std::shared_ptr<Keyboard::Keyboard>							m_keyboard;				/**< The Keyboard */
		std::vector<std::shared_ptr<Controllers::Gamepad>>			m_gamepads;				/**< Game Controllers */
	};
}
}