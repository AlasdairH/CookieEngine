#include <iostream>

#include "Initialiser.h"
#include "ServiceContainer.h"
#include "ServiceLocator.h"
#include "Window.h"

#include "Shader.h"
#include "Program.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include "Mesh.h"

#include "Renderer.h"

#include "Texture.h"

#include "GLM/common.hpp"
#include "GLM/ext.hpp"

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
	Services::ServiceLocator::getInitialiser().initSDL();
	Window *window = new Window("CookieEng", 720, 720);
	Services::ServiceLocator::getInitialiser().initOpenGL();

	// create vertex shader
	Graphics::Shader testVertShader(Graphics::SHADER_VERTEX);
	testVertShader.load("resources/shaders/vert.txt");

	// create fragment shader
	Graphics::Shader testFragShader(Graphics::SHADER_FRAGMENT);
	testFragShader.load("resources/shaders/frag.txt");

	// create shader program
	Graphics::Program testProgram;
	testProgram.attachShader(testVertShader);
	testProgram.attachShader(testFragShader);
	testProgram.link();

	// bind the shader program
	testProgram.bind();
	// set the ortho matrix
	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	// send the matrix to the shader
	testProgram.setUniformMat4f("u_MVP", proj);

	// load texture
	Graphics::Texture testTexture("resources/textures/texture.png");
	// texture bound to slot 0;
	testTexture.bind(0);
	// set shader to look for texture at slot 0
	testProgram.setUniform1i("u_texture", 0);

	Data::Mesh testMesh = Services::ServiceLocator::getFileManager().loadMesh("resources/models/plane.obj");

	// create a VAO for the vertex data
	Graphics::VertexArray testVAO;
	// create a VBO for the vertex data
	Graphics::VertexBuffer testVBO(Graphics::BUFFER_ARRAY);
	// create a layout for the data
	Graphics::VertexBufferLayout layout1;
	// push 3 floats for the position (x, y, z)
	layout1.push<float>(3);
	// push 2 floats for the texture coords (x, y)
	layout1.push<float>(2);
	// push 3 floats for the normals (x, y, z)
	layout1.push<float>(3);
	// add the buffer to the VAO
	testVAO.addBuffer(testVBO, layout1);
	// load data into the vertex VBO
	//testVBO.loadData(testMesh.vertices.data(), 0, sizeof(glm::vec3) * testMesh.vertices.size());
	testVBO.loadData(testMesh.vertices.data(), 0, (sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)) * testMesh.vertices.size());

	// create a VBO for the index data
	Graphics::VertexBuffer testIBO(Graphics::BUFFER_ELEMENT_ARRAY);
	// load data into the index VBO
	testIBO.loadData(testMesh.indices.data(), testMesh.indices.size(), sizeof(unsigned int) * testMesh.indices.size());

	Graphics::Renderer renderer;



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
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		renderer.draw(testVAO, testIBO, testProgram);

		window->swapBuffer();
	}

	delete window;

	return 0;
}