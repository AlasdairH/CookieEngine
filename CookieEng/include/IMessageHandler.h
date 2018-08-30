#pragma once

// cstdlib
#include <iostream>


// external libs


// program
#include "Macro.h"

#include "Message.h"


namespace CookieEng
{
namespace Messaging
{
	class Message;

	/*! @class IMessageHandler
	*	@brief The base class for engine objects that require the ability to receive messages.
	*
	*	This class is inherited from to allow overloading of the handleMessage method. This allows objects to receive messages from
	*	the MessageQueue or from other objects directly.
	*/
	class IMessageHandler
	{
	public:
		/** @brief Asynchronous loading of text files.
		*	@param _msg The message to be sent
		*
		*	The method to be overloaded by the derived class for handling the received message.
		*/
		virtual void handleMessage(const Message &_msg) {}
	};
}
}