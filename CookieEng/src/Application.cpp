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

	Core::ResourceLoader &resourceLoader = Core::ResourceLoader::getInstance();
	// load shaders and textures from file
	resourceLoader.fromFile("resources/assets/levels/test.lvl");

	Core::ResourceManager &resourceManager = Core::ResourceManager::getInstance();


	// camera
	Object::Camera testCamera;
	testCamera.setAspectRatio(window->getWidth() / (float)window->getHeight());
	testCamera.transform.translate(glm::vec3(0, 0, 8));

	Data::Mesh testMesh = Services::ServiceLocator::getFileManager().loadMesh("resources/models/Default.obj");

	// create a VAO for the vertex data
	Graphics::VertexArray testVAO;
	// create a VBO for the vertex data
	Graphics::VertexBuffer testVBO(Graphics::BUFFER_ARRAY);
	// add the buffer to the VAO
	testVAO.addBuffer(testVBO, testMesh.layout);
	// load data into the vertex VBO
	testVBO.loadData(testMesh.vertices.data(), 0, testMesh.layout.getStride() * testMesh.vertices.size());

	// create a VBO for the index data
	Graphics::VertexBuffer testIBO(Graphics::BUFFER_ELEMENT_ARRAY);
	// load data into the index VBO
	testIBO.loadData(testMesh.indices.data(), testMesh.indices.size(), sizeof(unsigned int) * testMesh.indices.size());

	// create framebuffer
	Graphics::FrameBuffer testFrameBuffer(window->getWidth(), window->getHeight());

	// create renderer
	Graphics::Renderer renderer;

	// create gameobject
	Core::IGameObject testGameObject;

	// test msg
	Services::ServiceLocator::getMessageQueue().addObserver(Messaging::MSG_KEY_DOWN, &testGameObject);
	Messaging::Message msg;
	msg.type = Messaging::MSG_KEY_DOWN;
	Services::ServiceLocator::getMessageQueue().pushMessage(msg);

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
			}
		}
		
		// update message queue on seperate thread
		testThreadPool.enqueue([] 
		{
			//Services::ServiceLocator::getMessageQueue().update();
		});
		

		// modify
		testGameObject.transform.rotate(0.5f, glm::vec3(1, 1, 1));

		resourceManager.getMaterial("BasicMaterial")->setMVP(testGameObject.transform.getMatrix(), glm::inverse(testCamera.transform.getMatrix()), testCamera.getProjectionMatrix());
		
		// draw to the framebuffer
		renderer.drawToFrameBuffer(testFrameBuffer, testVAO, testIBO, *resourceManager.getMaterial("BasicMaterial"));

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