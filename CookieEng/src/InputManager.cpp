#include "InputManager.h"

namespace CookieEng
{
namespace Input
{
	InputManager::InputManager()
	{
		m_keyboard.addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_W, SDLK_w);
		m_keyboard.addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_S, SDLK_s);
		m_keyboard.addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_A, SDLK_a);
		m_keyboard.addKey(Input::Keyboard::CNG_Keycode::CNG_KEY_D, SDLK_d);
	}
}
}