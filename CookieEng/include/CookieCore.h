#pragma once

// cstdlib
#include <iostream>

// external libs
#include "SDL/SDL.h"
#include "GL/glew.h"

// program
#include "Initialiser.h"
#include "ServiceContainer.h"
#include "ServiceLocator.h"

#include "Window.h"

#include "ResourceManager.h"
#include "ResourceLoader.h"
#include "InputManager.h"

#include "ThreadPool.h"

#include "Scene.h"

#include "Times.h"
#include "Macro.h"

#include "Keyboard.h"

#include "AudioSource.h"
#include "SoundEffect.h"

#define DEBUG

#undef main;

namespace CookieEng
{
	/*! @class CookieCore
	*	@brief The engine core class
	*
	*	The core class which contains the initialisation and start functions. These must be run for the engine to work properly.
	*/
	class CookieCore
	{
	public:
		/** @brief Core Ctor
		*
		*	Does nothing
		*/
		CookieCore();

		/** @brief Initialises CookieEngine
		*	@param _windowResolutionWidth The window width to create with the engine
		*	@param _windowResolutionHeight The filepath The window height to create with the engine
		*
		*	Does the essential engine initialisation such as starting services and running the constructors of any singletons. This ensures an explicit construction order is adheared to
		*	as some services require others to be started before they can work.
		*/
		void initialise(int _windowResolutionWidth, int _windowResolutionHeight);
		
		/** @brief Starts CookieEngine
		*
		*	Runs the start methods of any entities components in the scene at the beginning of the program and starts the engine loop.
		*/
		void start();		

	protected:
		Window		*m_window;						/**< The window with an OpenGL context to render to */

		bool		m_isInitialised = false;		/**< State flag for the engine initialisation state. Cannot start unless this is true. */
		bool		m_isPaused		= false;		/**< is updating paused */
	};
}