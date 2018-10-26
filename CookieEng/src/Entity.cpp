#include "Entity.h"

namespace CookieEng
{
	namespace ECS
	{
		Entity::Entity()
		{
			m_components.reserve(CNG_MAX_COMPONENTS);
			LOG_MESSAGE("Created Entity");
		}
	}
}
