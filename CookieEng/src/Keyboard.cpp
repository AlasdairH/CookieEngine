#include "Keyboard.h"

namespace CookieEng
{
namespace Input
{
namespace Keyboard
{
	Keyboard::Keyboard()
	{

	}

	void Keyboard::addKey(CNG_Keycode _cngKey, SDL_Keycode _sdlKey)
	{
		m_keys.insert(std::pair<SDL_Keycode, Key>(_cngKey, Key(_cngKey, _sdlKey)));
	}

	void Keyboard::update(SDL_KeyboardEvent &incomingEvent)
	{
		if (incomingEvent.type == SDL_KEYDOWN)
		{
			for (unsigned int i = 0; i < m_keys.size(); ++i)
			{
				if (incomingEvent.keysym.sym == m_keys[i].getSDLKeycode())
				{
					m_keys[i].setKeyDown(true);
				}
			}

		}

		if (incomingEvent.type == SDL_KEYUP)
		{
			for (unsigned int i = 0; i < m_keys.size(); ++i)
			{
				if (incomingEvent.keysym.sym == m_keys[i].getSDLKeycode())
				{
					m_keys[i].setKeyDown(false);
				}
			}

		}
	}
}
}
}