#include "Initialiser.h"

namespace CookieEng
{
namespace Services
{

	bool Initialiser::s_isSDLInitialised = false;
	bool Initialiser::s_isOpenGLInitialised = false;

	void Initialiser::initSDL()
	{
		LOG_MESSAGE("Initialising SDL");
		// attempt to initialise opengl
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			// something went wrong, exit program
			LOG_ERROR("Unable to Initialise SDL");
		}

		// set OpenGL 4.3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		LOG_MESSAGE("SDL Initialised");

		s_isSDLInitialised = true;
	}

	void Initialiser::initOpenGL()
	{
		LOG_MESSAGE("Initialising OpenGL");

		// GLEW has a problem with loading core OpenGL
		// See here: https://www.opengl.org/wiki/OpenGL_Loading_Library
		// The temporary workaround is to enable its 'experimental' features
		glewExperimental = GL_TRUE;

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			LOG_ERROR("GLEW failed to initialise ");
			return;
		}

		LOG_MESSAGE("Using GLEW " << glewGetString(GLEW_VERSION) );

		LOG_MESSAGE("OpenGL Vendor: " << glGetString(GL_VENDOR) );
		LOG_MESSAGE("OpenGL Renderer: " << glGetString(GL_RENDERER) );
		LOG_MESSAGE("OpenGL Version: " << glGetString(GL_VERSION) );
		LOG_MESSAGE("OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) );

		// enable face culling
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);

		LOG_MESSAGE("OpenGL Initialised" );

		s_isOpenGLInitialised = true;
	}

}
}

