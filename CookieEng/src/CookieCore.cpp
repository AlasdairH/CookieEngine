#include "CookieCore.h"

namespace CookieEng
{
	CookieCore::CookieCore()
	{
		LOG_MESSAGE("Hello World!");
	}

	void CookieCore::initialise(int _windowResolutionWidth, int _windowResolutionHeight)
	{
		LOG_MESSAGE("Beginning Engine Initialisation");
		if (m_isInitialised)
		{
			LOG_WARNING("Engine already initialised, stopping initialise function");
			return;
		}
		// assign services to the service locator using the service container
		Services::ServiceContainer serviceContainer;
		serviceContainer.assignServices();

		// initialise the Engine
		// init SDL
		Services::ServiceLocator::getInitialiser().initSDL();
		// create window for OpenGL context
		m_window = new Window("CookieEng", _windowResolutionWidth, _windowResolutionHeight);
		// init GLEW (OpenGL)
		Services::ServiceLocator::getInitialiser().initOpenGL();

		// instanciate the ResourceManager so the constructor is run
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();
		// instanciate the InputManager so the constructor is run
		Input::InputManager &inputManager = Input::InputManager::getInstance();

		// GL Funcs
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		//SDL_GL_SetSwapInterval(0);


		//m_scene = std::make_shared<Scene::Scene>();

		// thread test
		Threads::ThreadPool testThreadPool(6);

		Utilities::Times::deltaTime = 0;

		LOG_MESSAGE("Engine Initialisation Complete");
		m_isInitialised = true;
	}

	void CookieCore::start()
	{
		CNG_ACTIVE_SCENE->onStart();

		Input::InputManager &inputManager = Input::InputManager::getInstance();
		std::shared_ptr<Input::Keyboard::Keyboard> keyboard = inputManager.getKeyboard();

		Uint64 TIME_NOW = SDL_GetPerformanceCounter();
		Uint64 TIME_LAST = 0;

		LOG_MESSAGE("Starting Engine Loop");
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
				inputManager.onUpdate(incomingEvent);

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

				if (incomingEvent.type == SDL_MOUSEBUTTONDOWN)
				{
					if (CNG_ACTIVE_SCENE != nullptr)
					{
						// int x and y for state
						int x, y;
						SDL_GetMouseState(&x, &y);
						// float x and y for viewport correction and UI test
						float fx, fy;
						fx = (float)x;
						fy = CNG_ACTIVE_CAMERA->getViewportHeight() - (float)y;
						auto entity = CNG_ACTIVE_SCENE->getUIUnderScreenPosition(glm::vec2(fx, fy));

						if (entity != nullptr)
						{
							entity->getComponent<Components::GUI::UIButton>()->onMouseClick();
						}
					}
				}
			}

			// if there is a valid scene to update and render
			if (CNG_ACTIVE_SCENE != nullptr)
			{
				if (!m_isPaused)
				{
					CNG_ACTIVE_SCENE->onUpdate();
				}

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				CNG_ACTIVE_SCENE->draw();
				
				CNG_ACTIVE_SCENE->clean();
			}
			else
			{
				LOG_WARNING("No Active Scene Set");
			}


			m_window->swapBuffer();
		}
		LOG_MESSAGE("Stopping Engine");

		delete m_window;
	}
	
}