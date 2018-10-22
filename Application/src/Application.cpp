#include <iostream>

#include "CookieCore.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


#undef main

int main()
{
	using namespace CookieEng;

	CookieCore engine;
	engine.initialise(WINDOW_WIDTH, WINDOW_HEIGHT);

	CookieEng::ResMgmt::ResourceManager &resourceManager = CookieEng::ResMgmt::ResourceManager::getInstance();

	// when the scene is created, it will set itself as the main scene as there are no others
	CookieEng::Scene::Scene scene;

	CookieEng::ECS::Entity entity1;
	entity1.addComponent<Components::Renderable>();
	entity1.addComponent<Components::Transform>();
	entity1.getComponent<Components::Renderable>()->setMesh("DefaultMesh");
	entity1.getComponent<Components::Renderable>()->setMaterial("DefaultMaterial");
	CNG_ACTIVE_SCENE->addEntity(entity1); 

	Data::Ray ray1(glm::vec3(0, 0, 8), glm::vec3(0, 0.1f, -1));

	//entity1.getComponent<Components::Transform>()->translate(glm::vec3( 1.5f, 0, 0));

	Data::BoundingBox bb1 = entity1.getComponent<Components::Renderable>()->getBoundingBox();

	if (bb1.testCollision(ray1))
	{
		LOG_MESSAGE("COLLISION");
	}
	

	// when the camera is created, it will set itself as the main camera as there are no others
	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	CNG_ACTIVE_CAMERA->setFOV(1.0f);
	CNG_ACTIVE_CAMERA->transform.setPosition(glm::vec3(0, 0, 4));

	engine.start();


	return 0;
}
