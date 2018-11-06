#pragma once

// cstdlib

// external libs

// program

namespace CookieEng
{
namespace Input
{
namespace Keyboard
{
	class Key
	{
	public:
		bool isKeyDown() { return m_isDown; }

	protected:
		bool m_isDown = false;
	};
}
}
}
