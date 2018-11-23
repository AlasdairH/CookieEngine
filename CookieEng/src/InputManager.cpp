#include "InputManager.h"

namespace CookieEng
{
namespace Input
{
	InputManager::InputManager()
	{
		m_keyboard = std::make_shared<Keyboard::Keyboard>();

		m_keyboard->addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_W, SDLK_w);
		m_keyboard->addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_S, SDLK_s);
		m_keyboard->addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_A, SDLK_a);
		m_keyboard->addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_D, SDLK_d);

		if (SDL_NumJoysticks() < 1)
		{
			LOG_MESSAGE("InputManager: No Joysticks Detected");
		}
		else
		{
			for (int i = 0; i < SDL_NumJoysticks(); ++i)
			{
				LOG_MESSAGE("Game Controller " << i << " detected with name " << SDL_GameControllerNameForIndex(i));
				m_gamepads.push_back(std::make_shared <Controllers::Gamepad>());
				m_gamepads[m_gamepads.size() - 1]->assign(i);
				LOG_MESSAGE("Added GameController");
			}
		}
		


	}

	void InputManager::onUpdate(SDL_Event & _event)
	{
		m_keyboard->update(_event.key);

		for (unsigned int i = 0; i < m_gamepads.size(); ++i)
		{
			m_gamepads[i]->update();
		}
	}

	std::shared_ptr<Controllers::Gamepad> InputManager::getGamepad(int _id)
	{
		if (_id < m_gamepads.size())
		{
			return m_gamepads[_id];
		}
	}
}
}