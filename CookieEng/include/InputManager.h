#pragma once

// cstdlib
#include <memory>
#include <string>

// external libs

// program
#include "Macro.h"
#include "Utils.h"
#include "Keyboard.h"

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


		std::shared_ptr<Keyboard::Keyboard> getKeyboard() { return std::make_shared<Keyboard::Keyboard>(m_keyboard); }

		// ------------------------------------------------
		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

	protected:
		/** @brief InputManager Ctor
		*
		*	This is called on the first time the InputManager instance is grabbed.
		*/
		InputManager();

		Keyboard::Keyboard m_keyboard;
	};
}
}