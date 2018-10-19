#include <iostream>

#include "CookieCore.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


#undef main

int main()
{
	CookieEng::CookieCore engine;
	engine.initialise(WINDOW_WIDTH, WINDOW_HEIGHT);

	CookieEng::ResMgmt::ResourceManager &resourceManager = CookieEng::ResMgmt::ResourceManager::getInstance();

	// when the scene is created, it will set itself as the main scene as there are no others
	CookieEng::Scene::Scene scene;
	CookieEng::ECS::Entity entity;
	//entity.addComponent<CookieEng::Components::Transform>();
	entity.addComponent<CookieEng::Components::Renderable>();
	entity.getComponent<CookieEng::Components::Renderable>()->setMesh("BasicMesh");
	entity.getComponent<CookieEng::Components::Renderable>()->setMaterial("BasicMaterial");
	//CookieEng::Scene::Scene::activeScene->addEntity(entity);
	CNG_ACTIVE_SCENE->addEntity(entity); 

	entity.getComponent<CookieEng::Components::Transform>()->translate(glm::vec3(0, 1, 0));

	// when the camera is created, it will set itself as the main camera as there are no others
	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	CNG_ACTIVE_CAMERA->setFOV(1.0f);
	CNG_ACTIVE_CAMERA->transform.setPosition(glm::vec3(0, 0, 8));

	engine.start();


	return 0;
}
