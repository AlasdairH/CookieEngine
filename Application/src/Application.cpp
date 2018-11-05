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
	resourceManager.load<Resources::Mesh>("Mug", "resources/models/Mug.obj");

	// when the scene is created, it will set itself as the main scene as there are no others
	CookieEng::Scene::Scene scene;

	CookieEng::ECS::Entity gameController;
	gameController.addComponent<Components::Transform>();
	gameController.addComponent<Crumble::GameController>();
	CNG_ACTIVE_SCENE->addEntity(gameController);

	glm::vec3 cameraPos = glm::vec3(0.01f, 0.01f, 5.01f);

	// when the camera is created, it will set itself as the main camera as there are no others
	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	CNG_ACTIVE_CAMERA->setFOV(1.0f);
	CNG_ACTIVE_CAMERA->transform.setPosition(cameraPos);

	engine.start();


	return 0;
}
