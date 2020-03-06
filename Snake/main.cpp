#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<chrono>

//GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//Project includes
#include "Menu.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "GameController.h"
#include "Settings.h"
#include "WindowHandler.h"


int main(int argc, char* argv[])
{
	srand((unsigned)time(nullptr));

	Menu::OpenMenu();

	return EXIT_SUCCESS;

}