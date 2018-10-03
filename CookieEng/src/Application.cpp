#include <iostream>

#include "Initialiser.h"
#include "ServiceContainer.h"
#include "ServiceLocator.h"
#include "Window.h"

#include "VertexBuffer.h"
#include "VertexArray.h"

#include "Mesh.h"

#include "Renderer.h"

#include "Camera.h"

#include "GLM/common.hpp"
#include "GLM/ext.hpp"

#include "FrameBuffer.h"

#include "IGameObject.h"

#include "MessageQueue.h"
#include "Message.h"

#include "ResourceManager.h"
#include "ResourceLoader.h"

#include "ThreadPool.h"

#include "ECS.h"
#include "Renderable.h"

#define DEBUG

#undef main;

int main()
{
	using namespace CookieEng;

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// assign services to the service locator using the service container
	Services::ServiceContainer serviceContainer;
	serviceContainer.assignServices();

	// initialise the Engine
	// init SDL
	Services::ServiceLocator::getInitialiser().initSDL();
	// create window for OpenGL context
	Window *window = new Window("CookieEng", 1280, 720);
	// init GLEW (OpenGL)
	Services::ServiceLocator::getInitialiser().initOpenGL();

	//Core::ResourceLoader &resourceLoader = Core::ResourceLoader::getInstance();
	// load shaders and textures from file
	//resourceLoader.fromFile("resources/assets/levels/test.lvl");
	ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

	// load meshs
	resourceManager.load<Resources::Mesh>("BasicMesh", "resources/models/Default.obj");

	// load textures
	resourceManager.load<Resources::Texture>("BasicTexture", "resources/textures/Default.png");

	// load shaders
	resourceManager.load<Resources::ShaderProgram>("BasicShader", "resources/shaders/BasicShader.cngShader");

	// load materials
	resourceManager.load<Resources::Material>("BasicMaterial", "");
	resourceManager.get<Resources::Material>("BasicMaterial")->setShader("BasicShader");
	resourceManager.get<Resources::Material>("BasicMaterial")->setDiffuse("BasicTexture");

	ECS::Manager ecsManager;
	auto &entity(ecsManager.addEntity());
	entity.addComponent<Components::Transform>();
	entity.addComponent<Components::Renderable>();
	entity.getComponent<Components::Renderable>().setMesh("BasicMesh");
	entity.getComponent<Components::Renderable>().setMaterial("BasicMaterial");
	

	// camera
	Object::Camera testCamera;
	testCamera.setAspectRatio(window->getWidth() / (float)window->getHeight());
	testCamera.transform.translate(glm::vec3(0, 0, 8));

	// create framebuffer
	Graphics::FrameBuffer testFrameBuffer(window->getWidth(), window->getHeight());

	// create renderer
	Graphics::Renderer renderer;

	// thread test
	Threads::ThreadPool testThreadPool(6);

	LOG_MESSAGE("Starting Game Loop");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	const int targetFPS = 20;

	bool shouldQuit = false;
	while (!shouldQuit)
	{
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			if (incomingEvent.type == SDL_QUIT)
			{
				shouldQuit = true;
			}

			if (incomingEvent.type == SDL_WINDOWEVENT)
			{
				switch (incomingEvent.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					window->resize(incomingEvent.window.data1, incomingEvent.window.data2);
					break;
				}
			}

			if (incomingEvent.type == SDL_KEYDOWN)
			{
				if (incomingEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					shouldQuit = true;
				}
				if (incomingEvent.key.keysym.sym == SDLK_w)
				{
					testCamera.transform.translate(glm::vec3(0, 0, -1));
				}
				if (incomingEvent.key.keysym.sym == SDLK_s)
				{
					testCamera.transform.translate(glm::vec3(0, 0, 1));
				}
			}
		}
		
		// update message queue on seperate thread
		testThreadPool.enqueue([] 
		{
			//Services::ServiceLocator::getMessageQueue().update();
		});
		
		
		ecsManager.update();
		ecsManager.refresh();

		// modify
		entity.getComponent<Components::Transform>().rotate(0.5f, glm::vec3(1, 1, 1));

		resourceManager.get<Resources::Material>("BasicMaterial")->setMVP(entity.getComponent<Components::Transform>().getMatrix(), glm::inverse(testCamera.transform.getMatrix()), testCamera.getProjectionMatrix());
		
		// draw to the framebuffer
		//renderer.drawToFrameBuffer(testFrameBuffer, testVAO, testIBO, *resourceManager.get<Resources::Material>("BasicMaterial"));
		renderer.drawToFrameBuffer(
			testFrameBuffer,
			entity);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw the framebuffer to the screen
		testFrameBuffer.drawToScreen();

		window->swapBuffer();
	}
	LOG_MESSAGE("Stopping Engine");

	delete window;


	return 0;
}