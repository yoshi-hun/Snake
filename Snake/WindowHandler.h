#pragma once
#include <chrono>

struct GLFWwindow;
class Renderer;
class GameController;
struct Settings;

class WindowHandler
{
private:
	Renderer* renderer;
	GameController* gc;

	GLFWwindow* window;

	std::chrono::milliseconds timeStep;
public:
	std::chrono::milliseconds getCurrentTime();

	//Returns final score of the run
	unsigned Run();
	WindowHandler(Settings* s);
	~WindowHandler();
};
