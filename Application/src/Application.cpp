#include <iostream>

#include "CookieCore.h"
#include "GameController.h"

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

	CookieEng::ECS::Entity gameController;
	gameController.addComponent<Components::Transform>();
	gameController.addComponent<Crumble::GameController>();
	CNG_ACTIVE_SCENE->addEntity(gameController);

	LOG_MESSAGE("Game Controller Started");
	CookieEng::ECS::Entity object;
	object.addComponent<CookieEng::Components::Renderable>();
	object.addComponent<CookieEng::Components::Transform>();
	object.getComponent<Components::Transform>()->setPosition(glm::vec3(0, -0.5f, 0));
	object.getComponent<CookieEng::Components::Renderable>()->setMesh("DefaultMesh");
	object.getComponent<CookieEng::Components::Renderable>()->setMaterial("DefaultMaterial");
	CNG_ACTIVE_SCENE->addEntity(object);

	Data::Ray ray1(glm::vec3(0, 0, 8), glm::vec3(0, 0, -1));

	// when the camera is created, it will set itself as the main camera as there are no others
	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	CNG_ACTIVE_CAMERA->setFOV(1.0f);
	CNG_ACTIVE_CAMERA->transform.setPosition(glm::vec3(0, 0, 4));

	engine.start();


	return 0;
}
