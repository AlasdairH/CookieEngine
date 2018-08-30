#pragma once

// cstdlib
#include <iostream>


// external libs


// program
#include "Macro.h"

#include "IMessageHandler.h"

// TODO: Doxygen
// TODO: Finish

namespace CookieEng
{
namespace Core
{
	class GameObject : public Messaging::IMessageHandler
	{
	public:
		GameObject() {}
		~GameObject() {}

		void handleMessage(const Messaging::Message &_msg);
	};
}
}