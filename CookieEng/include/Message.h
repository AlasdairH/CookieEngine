#pragma once

// cstdlib
#include <iostream>
#include <string>

// external libs
#include "GLM/glm.hpp"

// program
#include "Macro.h"

// TODO: Doxygen

namespace CookieEng
{
namespace Messaging
{
	enum MessageType { MsgKeyDown, MsgKeyUp, MsgMouse };

	class Message
	{
	public:
		MessageType type;
	};

	class KeyMessage : public Message
	{
	public:
		std::string character;
	};

	class MouseMessage : public Message
	{
	public:
		glm::vec2 position;
	};
}
}
