#include "GameController.h"



namespace Crumble
{
	void GameController::onStart()
	{
		LOG_MESSAGE("Game Controller Started");
		CookieEng::ECS::Entity object;
		object.addComponent<CookieEng::Components::Renderable>();
		object.addComponent<CookieEng::Components::Transform>();
		object.addComponent<Crumble::Collectable>();
		object.getComponent<CookieEng::Components::Transform>()->setPosition(glm::vec3(0, 5, 0));
		object.getComponent<CookieEng::Components::Transform>()->setRotation(90, glm::vec3(1, 0, 0));
		object.getComponent<CookieEng::Components::Renderable>()->setMesh("Mug");
		object.getComponent<CookieEng::Components::Renderable>()->setMaterial("DefaultMaterial");
		CNG_ACTIVE_SCENE->addEntity(object);
	}

	void GameController::onUpdate()
	{

	}
}


