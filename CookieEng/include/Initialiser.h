#pragma once

// cstdlib
#include <iostream>

// external libs
#include "GL\glew.h"
#include "SDL\SDL.h"
#include "SDL_Mixer/SDL_mixer.h"

// program
#include "Macro.h"

namespace CookieEng
{
namespace Services
{
	/*! @class Initialiser
	*	@brief Initialisation for external libraries.
	*
	*	This class handles the initialisation and uninitialisation of external libraries such as SDL and OpenGL (GLEW).
	*/
	class Initialiser
	{
	public:
		Initialiser() { }

		/** @brief SDL Initialisation
		*
		*	Initialises SDL.
		*/
		void initSDL();

		/** @brief SDL Initialisation
		*
		*	Initialises OpenGL (GLEW). Before this is done, an OpenGL Context much exist!! (see Window class)
		*/
		void initOpenGL();

	protected:
		static bool		s_isSDLInitialised;			/**< A flag for the current SDL initialisation state */
		static bool		s_isOpenGLInitialised;		/**< A flag for the current OpenGL (GLEW) initialisation state */
	};

}
}