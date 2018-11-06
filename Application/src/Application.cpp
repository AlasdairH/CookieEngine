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

	srand(static_cast <unsigned>(time(0)));

	CookieEng::ResMgmt::ResourceManager &resourceManager = CookieEng::ResMgmt::ResourceManager::getInstance();

	LOG_MESSAGE("Loading Resources");
	// load meshs
	resourceManager.load<Resources::Mesh>("CookieMesh", "resources/models/Cookie.obj");
	resourceManager.load<Resources::Mesh>("MugMesh", "resources/models/CoffeeMug.obj");

	// load textures
	resourceManager.load<Resources::Texture>("CookieTexture", "resources/textures/Cookie.png");
	resourceManager.load<Resources::Texture>("GreyTexture", "resources/textures/Grey.png");

	// load shaders
	resourceManager.load<Resources::ShaderProgram>("DefaultShader", "resources/shaders/BasicShader.cngShader");

	// load materials
	resourceManager.load<Resources::Material>("CookieMaterial", "resources/materials/Cookie.cngMaterial");
	resourceManager.load<Resources::Material>("GreyMaterial", "resources/materials/Grey.cngMaterial");


	// when the scene is created, it will set itself as the main scene as there are no others
	CookieEng::Scene::Scene scene;

	CookieEng::ECS::Entity gameController;
	gameController.addComponent<Components::Transform>();
	gameController.addComponent<Crumble::GameController>();
	CNG_ACTIVE_SCENE->addEntity(gameController);

	glm::vec3 cameraPos = glm::vec3(0.01f, 0.01f, 10.00f);

	// when the camera is created, it will set itself as the main camera as there are no others
	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	CNG_ACTIVE_CAMERA->setFOV(1.0f);
	CNG_ACTIVE_CAMERA->transform.setPosition(cameraPos);

	engine.start();


	return 0;
}
