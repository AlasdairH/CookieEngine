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

#include "GLM/common.hpp"

#define DEBUG


#undef main;

int main()
{
	using namespace CookieEng;

	// assign services to the service locator using the service container
	Services::ServiceContainer serviceContainer;
	serviceContainer.assignServices();

	// initialise the Engine
	Services::ServiceLocator::getInitialiser().initSDL();
	Window *window = new Window("CookieEng");
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

	/*
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	*/

	Data::Mesh testMesh = Services::ServiceLocator::getFileManager().loadMesh("resources/models/sphere.obj");


	Graphics::VertexArray testVAO;

	//glGenVertexArrays(1, &VAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO);

	// create a VBO for the vertex data
	Graphics::VertexBuffer testVBO(Graphics::BUFFER_ARRAY);
	// create a layout for the data
	Graphics::VertexBufferLayout layout1;
	// push 3 floats to the layout (the x, y and z of the vertex)
	layout1.push<float>(3);
	// add the buffer to the VAO
	testVAO.addBuffer(testVBO, layout1);
	// load data into the vertex VBO
	testVBO.loadData(testMesh.vertices.data(), testMesh.vertices.size() * 3, sizeof(glm::vec3) * testMesh.vertices.size());

	// create a VBO for the index data
	Graphics::VertexBuffer testIBO(Graphics::BUFFER_ELEMENT_ARRAY);
	// load data into the index VBO
	testIBO.loadData(testMesh.indices.data(), testMesh.indices.size(), sizeof(unsigned int) * testMesh.indices.size());

	/*
	glVertexAttribPointer(
		0,						// index
		3,						// size
		GL_FLOAT,				// type
		GL_FALSE,				// normalised
		3 * sizeof(float),		// stride
		(void*)0);				// pointer (offset)
	glEnableVertexAttribArray(0);
	*/

	glEnable(GL_DEPTH_TEST);

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