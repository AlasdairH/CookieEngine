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
	//TODO: Add mouse

	/*! @class InputManager
	*	@brief An Input Manager singleton for getting peripheral input
	*
	*	This singleton class gets and handles input from peripherals such as the keyboard and gamepads.
	*/
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

		/** @brief Gets whether a controller is connected and valid
		*	@param _id the controller ID to test for validity
		*
		*	Takes an ID and tests to see if the controller exists
		*/
		inline bool validController(int _id) { if ((unsigned int)_id < m_gamepads.size()) return true; else return false; }

		/** @brief Returns a pointer to a Gamepad
		*	@param _id The controller to get
		*
		*	Takes a controller ID and returns the controller with that ID if it exists
		*/
		std::shared_ptr<Controllers::Gamepad> getGamepad(int _id);
		/** @brief Gets the main keyboard
		*
		*	Returns a pointer to the keyboard
		*/
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