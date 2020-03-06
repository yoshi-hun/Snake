#include <iostream>

#include "Settings.h"

Settings::Settings()
{
	// Default settings
	squareDimension = 30;
	padding = 2;
	border = 30;
	rows = 12;
	columns = 18;
	difficulty = 3;
	height = 0;
	width = 0;

	glfwInit();
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	std::cout << "Snake game initial setup!" << std::endl;
	std::cout << "Rows (default 12): ";
	unsigned _rows;
	std::cin >> _rows;
	if (std::cin.fail() || _rows < 2)
	{
		std::cout << "Wrong input, using default setting" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		_rows = rows;
	}

	height = border * 2 + _rows * (squareDimension + padding) - padding;

	if (height > mode->height)
	{
		throw new ExceedsScreenResolutionException("HEIGHT");
	}
	else
	{
		rows = _rows;
	}

	std::cout << "Columns (default 18): ";
	unsigned _cols;
	std::cin >> _cols;
	if (std::cin.fail() || _cols < 2)
	{
		std::cout << "Wrong input, using default setting" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		_cols = columns;
	}

	width = border * 2 + _cols * (squareDimension + padding) - padding;


	if (width > mode->width)
	{
		throw new ExceedsScreenResolutionException("WIDTH");
	}
	else
	{
		columns = _cols;
	}

	std::cout << "Difficulty (1-9) (default 3): ";
	unsigned _diff;
	std::cin >> _diff;
	if (std::cin.fail() || _diff < 1 || _diff > 9)
	{
		std::cout << "Wrong input, using default setting" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		_diff = difficulty;
	}
	difficulty = _diff;
}
