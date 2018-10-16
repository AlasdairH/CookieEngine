#pragma once

// cstdlib
#include <iostream>

// external libs
#include "SDL/SDL.h"
#include "GL/glew.h"

// progra
#include "Initialiser.h"
#include "ServiceContainer.h"
#include "ServiceLocator.h"

#include "Window.h"

#include "ResourceManager.h"
#include "ResourceLoader.h"

#include "ThreadPool.h"

#include "Scene.h"

#include "Times.h"

#define DEBUG

#undef main;

namespace CookieEng
{
	class CookieCore
	{
	public:
		CookieCore();

		void initialise()
		{
			// assign services to the service locator using the service container
			Services::ServiceContainer serviceContainer;
			serviceContainer.assignServices();

			// initialise the Engine
			// init SDL
			Services::ServiceLocator::getInitialiser().initSDL();
			// create window for OpenGL context
			m_window = new Window("CookieEng", 1280, 720);
			// init GLEW (OpenGL)
			Services::ServiceLocator::getInitialiser().initOpenGL();

			// instanciate the ResourceManager so the constructor is run
			ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

			// GL Funcs
			glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			//SDL_GL_SetSwapInterval(0);

			m_scene = std::make_shared<Scene::Scene>();

			// thread test
			Threads::ThreadPool testThreadPool(6);

			Utilities::Times::deltaTime = 0;
		}

		void start()
		{
			LOG_MESSAGE("Starting Game Loop");

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			Uint64 TIME_NOW = SDL_GetPerformanceCounter();
			Uint64 TIME_LAST = 0;

			bool shouldQuit = false;
			while (!shouldQuit)
			{
				// deltaTime calculations
				TIME_LAST = TIME_NOW;
				TIME_NOW = SDL_GetPerformanceCounter();
				Utilities::Times::deltaTime = ((double)((TIME_NOW - TIME_LAST) * 1000 / (double)SDL_GetPerformanceFrequency())) * 0.001f;

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
							m_window->resize(incomingEvent.window.data1, incomingEvent.window.data2);
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
							//testCamera.transform.translate(glm::vec3(0, 0, -10) * Utilities::Times::deltaTime);
						}
						if (incomingEvent.key.keysym.sym == SDLK_s)
						{
							//testCamera.transform.translate(glm::vec3(0, 0, 10) * Utilities::Times::deltaTime);
						}
					}
				}

				/*
				// update message queue on seperate thread
				testThreadPool.enqueue([]
				{
					//Services::ServiceLocator::getMessageQueue().update();
				});
				*/

				m_scene->onUpdate();

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_scene->draw();

				m_window->swapBuffer();
			}
			LOG_MESSAGE("Stopping Engine");

			delete m_window;
		}

	protected:
		std::shared_ptr<Scene::Scene> m_scene;

		Window *m_window;
	};
}