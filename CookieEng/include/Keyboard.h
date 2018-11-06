#pragma once

// cstdlib
#include <string>
#include <unordered_map>

// external libs

// program
#include "InputKey.h"

namespace CookieEng
{
namespace Input
{
namespace Keyboard
{
	class Keyboard
	{
	public:
		Keyboard();
		void addKey(std::string _key);

		bool isKeyDown(std::string _key) { return m_keys[_key].isKeyDown(); }

	protected:
		std::unordered_map<std::string, Key> m_keys;
	};
}
}
}
