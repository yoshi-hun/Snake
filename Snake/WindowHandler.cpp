#include <iostream>
#include <cstdlib>
#include <exception>

#include "WindowHandler.h"
#include "Settings.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "GameController.h"


std::chrono::milliseconds WindowHandler::getCurrentTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

InputHandler* inputHandler = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (inputHandler == nullptr)
	{
		std::cerr << "Input handler not initialized" << std::endl;
		throw new std::exception("Input handler not initialized");
	}
	inputHandler->handleInput(key, scancode, action, mods);
}


WindowHandler::WindowHandler(Settings* s)
{
	timeStep = std::chrono::milliseconds{ 1000 / s->difficulty };

	glfwInit();

	window = glfwCreateWindow(s->width, s->height, "Snake", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr)
	{
		glfwTerminate();
		throw new std::exception("Failed to create window");
	}

	glfwMakeContextCurrent(window);

	glViewport(0, 0, screenWidth, screenHeight);

	if (inputHandler != nullptr)
	{
		throw new std::exception("Multiple instances of the game window initialized");
	}
	inputHandler = new InputHandler();
	renderer = new Renderer(s);
	gc = new GameController(s);

	glfwSetKeyCallback(window, key_callback);

	// BGColor
	glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
}

unsigned WindowHandler::Run()
{
	std::chrono::milliseconds lastCheck = getCurrentTime();
	// Game loop
	while (!glfwWindowShouldClose(window) && gc->GetState() == GameState::PLAYING)
	{
		// Poll events (keyboard, mouse, etc)
		glfwPollEvents();

		// Render
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnableClientState(GL_COLOR_ARRAY);

		if (lastCheck < (getCurrentTime() - timeStep))
		{
			lastCheck = getCurrentTime();
			gc->Propagate(inputHandler->getLastDirection());
		}

		renderer->Render(gc->GetBoard());

		glfwSwapBuffers(window);
	}
	return gc->GetScore();
}


WindowHandler::~WindowHandler()
{
	glfwTerminate();
	delete inputHandler;
	inputHandler = nullptr;
	delete renderer;
	delete gc;
}
