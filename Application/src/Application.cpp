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
	entity1.getComponent<Components::Renderable>()->setMesh("BasicMesh");
	entity1.getComponent<Components::Renderable>()->setMaterial("BasicMaterial");
	CNG_ACTIVE_SCENE->addEntity(entity1); 

	CookieEng::ECS::Entity entity2;
	entity2.addComponent<Components::Transform>();
	entity2.addComponent<Components::Renderable>();
	entity2.getComponent<Components::Renderable>()->setMesh("BasicMesh");
	entity2.getComponent<Components::Renderable>()->setMaterial("BasicMaterial");
	CNG_ACTIVE_SCENE->addEntity(entity2);

	entity1.getComponent<Components::Transform>()->translate(glm::vec3( 1.5f, 0, 0));
	entity2.getComponent<Components::Transform>()->translate(glm::vec3(-1.5f, 0, 0));

	Data::BoundingBox bb1 = entity1.getComponent<Components::Renderable>()->getBoundingBox();
	Data::BoundingBox bb2 = entity2.getComponent<Components::Renderable>()->getBoundingBox();
	

	// when the camera is created, it will set itself as the main camera as there are no others
	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	CNG_ACTIVE_CAMERA->setFOV(1.0f);
	CNG_ACTIVE_CAMERA->transform.setPosition(glm::vec3(0, 0, 8));

	engine.start();


	return 0;
}
