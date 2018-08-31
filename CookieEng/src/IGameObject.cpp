#include "IGameObject.h"

namespace CookieEng
{
namespace Core
{
	void IGameObject::handleMessage(const Messaging::Message & _msg)
	{
		if (_msg.type == Messaging::MSG_KEY_DOWN)
		{
			LOG_MESSAGE("Key Pressed");
		}
		
	}
}
}

