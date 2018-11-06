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

	void Keyboard::addKey(std::string _key)
	{
		m_keys.insert(std::pair<std::string, Key>(_key, Key()));
	}
}
}
}