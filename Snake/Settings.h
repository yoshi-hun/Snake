#pragma once

#include <exception>

#include <GLFW/glfw3.h>

struct Settings
{
public:
	Settings();
	~Settings() {};
	unsigned squareDimension;
	unsigned padding;
	unsigned border;
	unsigned rows;
	unsigned columns;
	unsigned difficulty;
	GLint height;
	GLint width;
};

class ExceedsScreenResolutionException : std::exception
{
	std::string _dimension;
public:
	ExceedsScreenResolutionException(std::string dimension) : _dimension(dimension) {}
	std::string GetErrorMsg()
	{
		return "Game field exceeds screen in dimension: " + _dimension + ".\n";
	}
};

