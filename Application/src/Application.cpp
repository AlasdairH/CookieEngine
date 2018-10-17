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

	CookieEng::Scene::Scene scene;
	CookieEng::ECS::Entity entity;
	entity.addComponent<CookieEng::Components::Transform>();
	entity.addComponent<CookieEng::Components::Renderable>();
	entity.getComponent<CookieEng::Components::Renderable>()->setMesh("BasicMesh");
	entity.getComponent<CookieEng::Components::Renderable>()->setMaterial("BasicMaterial");
	//CookieEng::Scene::Scene::activeScene->addEntity(entity);
	scene.addEntity(entity);

	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	camera.setFOV(1.0f);
	camera.transform.setPosition(glm::vec3(0, 0, 8));

	engine.start();


	return 0;
}
