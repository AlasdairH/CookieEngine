#include "MessageQueue.h"

namespace CookieEng
{
namespace Services
{
	void MessageQueue::pushMessage(const Messaging::Message & _msg)
	{
		m_messageQueue.push(_msg);
	}

	void MessageQueue::update()
	{
		while (!m_messageQueue.empty())
		{
			
			Messaging::Message &msg = m_messageQueue.front();

			// handle type: MSG_UNKNOWN
			if (msg.type == Messaging::MSG_UNKNOWN)
			{
				// loop through observers
				for (unsigned int i = 0; i < m_obs_MSG_UNKNOWN.size(); ++i)
				{
					m_obs_MSG_UNKNOWN[i]->handleMessage(msg);
				}
			}

			// handle type: MSG_KEY_DOWN
			else if (msg.type == Messaging::MSG_KEY_DOWN)
			{
				// loop through observers
				for (unsigned int i = 0; i < m_obs_MSG_KEY_DOWN.size(); ++i)
				{
					m_obs_MSG_KEY_DOWN[i]->handleMessage(msg);
				}
			}

			// handle type: MSG_KEY_UP
			else if (msg.type == Messaging::MSG_KEY_UP)
			{
				// loop through observers
				for (unsigned int i = 0; i < m_obs_MSG_KEY_UP.size(); ++i)
				{
					m_obs_MSG_KEY_UP[i]->handleMessage(msg);
				}
			}

			// handle type: MSG_MOUSE
			else if (msg.type == Messaging::MSG_MOUSE)
			{
				// loop through observers
				for (unsigned int i = 0; i < m_obs_MSG_MOUSE.size(); ++i)
				{
					m_obs_MSG_MOUSE[i]->handleMessage(msg);
				}
			}

			m_messageQueue.pop();
		}
	}
	void MessageQueue::addObserver(const Messaging::MessageType _msgType, Messaging::IMessageHandler * _obj)
	{
		switch (_msgType)
		{
		case Messaging::MSG_UNKNOWN:
			m_obs_MSG_UNKNOWN.push_back(_obj);
			break;

		case Messaging::MSG_KEY_DOWN:
			m_obs_MSG_KEY_DOWN.push_back(_obj);
			break;

		case Messaging::MSG_KEY_UP:
			m_obs_MSG_KEY_UP.push_back(_obj);
			break;

		case Messaging::MSG_MOUSE:
			m_obs_MSG_MOUSE.push_back(_obj);
			break;

		default:
			LOG_WARNING("Could not add Observer: Message type not implemented");
			break;
		}
	}
}
}