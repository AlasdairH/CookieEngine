#pragma once

// cstdlib
#include <iostream>
#include <string>

// external libs
#include "GLM/glm.hpp"

// program
#include "Macro.h"
#include "IMessageHandler.h"

namespace CookieEng
{
namespace Messaging
{
	enum MessageType { MSG_UNKNOWN, MSG_KEY_DOWN, MSG_KEY_UP, MSG_MOUSE };

	// forward declaration
	class IMessageHandler;

	/*! @class Message
	*	@brief A Message for passing around the engine
	*
	*	Messages contain a type and data that can be used by classes that inherit from IMessageHandler.
	*/
	class Message
	{
	public:
		MessageType type = MSG_UNKNOWN;						/**< The Message Type */

		// TODO: Add Data
	};
}
}
