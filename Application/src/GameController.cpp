#include "GameController.h"



namespace Crumble
{
	void GameController::onStart()
	{
		LOG_MESSAGE("Game Controller Started");
		CookieEng::ECS::Entity object;
		object.addComponent<CookieEng::Components::Renderable>();
		object.addComponent<CookieEng::Components::Transform>();
		object.getComponent<CookieEng::Components::Transform>()->setPosition(glm::vec3(0, 0, 0));
		object.getComponent<CookieEng::Components::Renderable>()->setMesh("DefaultMesh");
		object.getComponent<CookieEng::Components::Renderable>()->setMaterial("DefaultMaterial");
		CNG_ACTIVE_SCENE->addEntity(object);
	}

	void GameController::onUpdate()
	{
		auto object = CNG_ACTIVE_SCENE->getEntity(1);

		CookieEng::Data::Ray ray(CNG_ACTIVE_CAMERA->transform.getPositionVec3(), glm::vec3(0, -0.1f, -1));
		object->getComponent<CookieEng::Components::Transform>()->setPosition(ray.getPoint(5));
		
		CookieEng::Data::BoundingBox bb1 = object->getComponent<CookieEng::Components::Renderable>()->getBoundingBox();

		
		
		if (bb1.testCollision(ray))
		{
			LOG_MESSAGE("Raycast Hit");
		}
		
	}
}


