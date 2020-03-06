#pragma once

#include <GLFW/glfw3.h>

#include "Direction.h"

class InputHandler
{
public:
	void handleInput(int key, int scancode, int action, int mods);
	Direction getLastDirection();

	InputHandler();
	~InputHandler();
private:
	Direction lastDirection;
};

