#include<cstdlib>
#include<ctime>

//GLFW
#include <GLFW/glfw3.h>

//Project includes
#include "Menu.h"


int main(int argc, char* argv[])
{
	srand((unsigned)time(nullptr));

	Menu::OpenMenu();

	return EXIT_SUCCESS;

}