#pragma once

// cstdlib
#include <iostream>


// external libs


// program
#include "Macro.h"
#include "Transform.h"
#include "IMessageHandler.h"

// TODO: Doxygen
// TODO: Finish

namespace CookieEng
{
namespace Core
{
	class IGameObject : public Messaging::IMessageHandler
	{
	public:
		IGameObject() {}
		~IGameObject() {}

	protected:
	};
}
}