#include "GameController.h"



namespace Crumble
{
	void GameController::onStart()
	{
		CookieEng::ECS::Entity player;
		player.addComponent<CookieEng::Components::Transform>();
		player.addComponent<CookieEng::Components::Renderable>();
		player.addComponent<Crumble::Player>();
		CNG_ACTIVE_SCENE->addEntity(player);
	}

	void GameController::onUpdate()
	{
		// check if a new cookie is to be spawned
		float test = CookieEng::Utilities::UtilsFloat::randFloat(0.0f, 1.0f);
		if (test > 0.99f)
		{
			int xpos = (int)(CookieEng::Utilities::UtilsFloat::randFloat(-8.0f, 8.0f) / 2) * 2;
			CookieEng::ECS::Entity object;
			object.addComponent<CookieEng::Components::Transform>();
			object.getComponent<CookieEng::Components::Transform>()->setPosition(glm::vec3(xpos, 5, 0));
			object.addComponent<CookieEng::Components::Renderable>();
			object.addComponent<Crumble::Collectable>();
			m_collectables.emplace_back(CNG_ACTIVE_SCENE->addEntity(object));
		}
	}
}


