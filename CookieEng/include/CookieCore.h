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

		void initialise(int _windowResolutionWidth, int _windowResolutionHeight);
		void start();

	protected:
		//std::shared_ptr<Scene::Scene> m_scene;

		Window *m_window;

		bool m_isInitialised = false;
	};
}
