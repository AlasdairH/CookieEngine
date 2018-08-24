#include <iostream>

#include "Initialiser.h"
#include "ServiceContainer.h"
#include "ServiceLocator.h"
#include "Window.h"

#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include "Mesh.h"

#include "Renderer.h"

#include "Texture.h"

#include "Camera.h"

#include "GLM/common.hpp"
#include "GLM/ext.hpp"

#include "FrameBuffer.h"

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
	Window *window = new Window("CookieEng", 1280, 720);
	Services::ServiceLocator::getInitialiser().initOpenGL();

	// create shader program
	Graphics::ShaderProgram testShader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

	// bind the shader program
	testShader.bind();

	// load texture
	Graphics::Texture testTexture("resources/textures/texture.png");
	// texture bound to slot 0;
	testTexture.bind(0);
	// set shader to look for texture at slot 0
	testShader.setUniform1i("u_texture", 0);

	// camera
	Object::Camera testCamera;
	testCamera.setAspectRatio(window->getWidth() / (float)window->getHeight());
	testCamera.transform.translate(glm::vec3(0, 0, 10));
	
	// model
	Attribute::Transform model;

	Data::Mesh testMesh = Services::ServiceLocator::getFileManager().loadMesh("resources/models/cube.obj");

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
	testVBO.loadData(testMesh.vertices.data(), 0, (sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)) * testMesh.vertices.size());

	// create a VBO for the index data
	Graphics::VertexBuffer testIBO(Graphics::BUFFER_ELEMENT_ARRAY);
	// load data into the index VBO
	testIBO.loadData(testMesh.indices.data(), testMesh.indices.size(), sizeof(unsigned int) * testMesh.indices.size());

	Graphics::FrameBuffer testFrameBuffer(window->getWidth(), window->getHeight());

	Graphics::Renderer renderer;
	//renderer.setFrameBuffer(&testFrameBuffer);

	

	LOG_MESSAGE("Starting Game Loop");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

		// modify
		 model.rotate(0.5f, glm::vec3(1, 1, 1));

		// calculate the MVP
		glm::mat4 MVP = testCamera.getProjectionMatrix() * glm::inverse(testCamera.transform.getMatrix()) * model.getMatrix();
		// bind the shader
		testShader.bind();
		// set the MVP Matrix on the GPU
		testShader.setUniformMat4f("u_MVP", MVP);
		// bind the texture
		testTexture.bind();
		
		// draw to the framebuffer
		renderer.drawToFrameBuffer(testFrameBuffer, testVAO, testIBO, testShader);

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