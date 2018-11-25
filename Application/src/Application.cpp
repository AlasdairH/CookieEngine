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
	resourceManager.load<Resources::Mesh>("GUIPlane", "resources/models/GUIPlane.obj");

	// load textures
	resourceManager.load<Resources::Texture>("CookieTexture", "resources/textures/Cookie.png");
	resourceManager.load<Resources::Texture>("GreyTexture", "resources/textures/Grey.png");
	resourceManager.load<Resources::Texture>("ButtonTexture", "resources/textures/Button.png");
	resourceManager.load<Resources::Texture>("WinLabelTexture", "resources/textures/Win.png");

	// load shaders
	resourceManager.load<Resources::ShaderProgram>("DefaultShader", "resources/shaders/BasicShader.cngShader");
	resourceManager.load<Resources::ShaderProgram>("GUIShader", "resources/shaders/GUI/GUIShader.cngShader");

	// load materials
	resourceManager.load<Resources::Material>("CookieMaterial", "resources/materials/Cookie.cngMaterial");
	resourceManager.load<Resources::Material>("GreyMaterial", "resources/materials/Grey.cngMaterial");
	resourceManager.load<Resources::Material>("GUIMaterial", "resources/materials/GUI.cngMaterial");
	resourceManager.load<Resources::Material>("WinLabelMaterial", "resources/materials/Win.cngMaterial");

	// load sounds
	resourceManager.load<Resources::SoundEffect>("DunkSound", "resources/sounds/dunk.wav");

	// when the camera is created, it will set itself as the main camera as there are no others
	CookieEng::Object::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	CNG_ACTIVE_CAMERA->setFOV(1.0f);
	glm::vec3 cameraPos = glm::vec3(0.01f, 0.01f, 10.00f);
	CNG_ACTIVE_CAMERA->transform.setPosition(cameraPos);

	// when the scene is created, it will set itself as the main scene as there are no others
	CookieEng::Scene::Scene scene;

	CookieEng::ECS::Entity gameController;
	gameController.addComponent<Components::Transform>();
	gameController.addComponent<Crumble::GameController>();
	CNG_ACTIVE_SCENE->addEntity(gameController);

	CookieEng::ECS::Entity uiPauseButton;
	uiPauseButton.addComponent<Components::Transform>();
	uiPauseButton.addComponent<CookieEng::Components::GUI::UIButton>();
	auto button = uiPauseButton.getComponent<CookieEng::Components::GUI::UIButton>();
	button->setWidth(150);
	button->setHeight(100);
	button->setPosition(glm::vec2(50, 50));
	// set button action
	button->setAction([]
	{
		CNG_ACTIVE_SCENE->togglePause();
	}
	);
	CNG_ACTIVE_SCENE->addEntity(uiPauseButton);

	engine.start();


	return 0;
}
