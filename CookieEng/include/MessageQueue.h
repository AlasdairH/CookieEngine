#pragma once

// cstdlib
#include <queue>

// external libs


// program
#include "IMessageHandler.h"
#include "Message.h"

namespace CookieEng
{
namespace Services
{
	/*! @class MessageQueue
	*	@brief A queue for distributing messages to Observers
	*
	*	Message handlers can register as observers to a specific message type and the message queue will distribute
	*	messages of tha type to the observers as they are handled by the queue. TODO: Msg Expand
	*/
	class MessageQueue : public Messaging::IMessageHandler
	{
	public:
		/** @brief Adds a message to the queue
		*	@param _msg The message to push to the queue
		*
		*	Adds a message to the queue.
		*/
		void pushMessage(const Messaging::Message &_msg);

		/** @brief Handles the queue of messages
		*
		*	This method runs through the queue of messages and handles them one by one. The
		*	message type is read and then messages are distributed to the observers of that type.
		*/
		void update();

		/** @brief Adds a message to the queue
		*	@param _msgType The type that the handler wants to observe
		*	@param _obj The message handler to assign as an observer
		*
		*	Adds an observer of a specified type to the corresponding member vector (m_obs_MSG_).
		*/
		void addObserver(const Messaging::MessageType _msgType, Messaging::IMessageHandler *_obj);

	protected:
		std::queue<Messaging::Message>				m_messageQueue;			/**< The Message Queue */

		std::vector<Messaging::IMessageHandler *>	m_obs_MSG_UNKNOWN;		/**< The observer list for Uknown Messages */
		std::vector<Messaging::IMessageHandler *>	m_obs_MSG_KEY_DOWN;		/**< The observer list for Key Down Messages */
		std::vector<Messaging::IMessageHandler *>	m_obs_MSG_KEY_UP;		/**< The observer list for Key Uo Messages */
		std::vector<Messaging::IMessageHandler *>	m_obs_MSG_MOUSE;		/**< The observer list for Mouse Messages */
	};
}
}
