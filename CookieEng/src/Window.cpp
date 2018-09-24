#include "Window.h"

namespace CookieEng
{
	Window::Window(const std::string _title, const int _width, const int _height)
	{
		m_window = SDL_CreateWindow(_title.c_str(), 
			50, 50, 
			_width, _height, 
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		m_openGLContext = SDL_GL_CreateContext(m_window);

		resize(_width, _height);
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(m_window);
	}

	void Window::resize(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;

		LOG_MESSAGE("Window resised to: " << m_width << ", " << m_height);

		float aspect = (float)m_width / (float)m_height;
		glViewport(0, 0, m_width, m_height);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND); //Enable alpha blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (float)m_width / (float)m_height, 0.01f, 100.0f);
		gluOrtho2D(0.0, m_width, m_height * aspect, 0.0);
		glMatrixMode(GL_MODELVIEW);

	}

	
}