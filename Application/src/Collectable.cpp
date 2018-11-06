#include "Collectable.h"

namespace Crumble
{
	void Collectable::onInit()
	{
		parent->getComponent<CookieEng::Components::Transform>()->setRotation(90, glm::vec3(1, 0, 0));
		parent->getComponent<CookieEng::Components::Renderable>()->setMesh("CookieMesh");
		parent->getComponent<CookieEng::Components::Renderable>()->setMaterial("CookieMaterial");
	}

	void Collectable::onStart()
	{

	}

	void Collectable::onUpdate()
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->translate(glm::vec3(0, -1, 0) * CNG_DELTA_TIME);
	}
}



