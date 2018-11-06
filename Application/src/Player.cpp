#include "Player.h"

namespace Crumble
{
	void Player::onInit()
	{
		parent->getComponent<CookieEng::Components::Transform>()->setPosition(glm::vec3(0, -4, 0));
		parent->getComponent<CookieEng::Components::Transform>()->setRotation(90, glm::vec3(0, 1, 0));
		parent->getComponent<CookieEng::Components::Renderable>()->setMesh("MugMesh");
		parent->getComponent<CookieEng::Components::Renderable>()->setMaterial("GreyMaterial");
	}

	void Player::onStart()
	{

	}

	void Player::onUpdate()
	{

	}
}



