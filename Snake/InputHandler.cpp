#include "InputHandler.h"

void InputHandler::handleInput(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		lastDirection = Direction::UP;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		lastDirection = Direction::DOWN;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		lastDirection = Direction::LEFT;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		lastDirection = Direction::RIGHT;
	}
}

Direction InputHandler::getLastDirection()
{
	return lastDirection;
}


InputHandler::InputHandler()
{
	lastDirection = Direction::NONE;
}


InputHandler::~InputHandler()
{
}
