#include "Collectable.h"



namespace Crumble
{
	void Collectable::onStart()
	{

	}

	void Collectable::onUpdate()
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->translate(glm::vec3(0, -1, 0) * CNG_DELTA_TIME);
	}
}



