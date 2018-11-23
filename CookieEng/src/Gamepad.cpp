#include "Gamepad.h"

namespace CookieEng
{
namespace Input
{
namespace Controllers
{
	Gamepad::Gamepad()
	{

	}

	void Gamepad::update()
	{
		SDL_GameControllerUpdate();
	}

	void Gamepad::assign(int _index)
	{
		m_gameController = SDL_GameControllerOpen(_index);
		if (m_gameController == NULL)
		{
			LOG_WARNING("Failed to assign gameController to game controller");
		}
		m_joystick = SDL_GameControllerGetJoystick(m_gameController);
		if (m_joystick == NULL)
		{
			LOG_WARNING("Failed to assign joystick to game controller");
		}
	}
	float Gamepad::getAxis(std::string _axis)
	{
		SDL_GameControllerAxis axis = SDL_GameControllerGetAxisFromString(_axis.c_str());
		if (axis == SDL_CONTROLLER_AXIS_INVALID || m_gameController == NULL)
		{
			LOG_WARNING("Unable to find axis " << _axis.c_str());
			return -1;
		}
		float value = SDL_GameControllerGetAxis(m_gameController, axis);
		return value / 32767.0f;
	}
}
}
}