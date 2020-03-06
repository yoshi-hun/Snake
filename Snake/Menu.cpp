#include <iostream>
#include <cstdlib>
#include <string>

#include "Menu.h"
#include "Settings.h"
#include "WindowHandler.h"
#include "HighScores.h"

Settings* Menu::settings = nullptr;

void Menu::PrintMenu()
{
	std::cout << std::endl;
	std::cout << "============= Snake ==========" << std::endl;
	std::cout << "1.) Play game" << std::endl;
	std::cout << "2.) Redefine settings" << std::endl;
	std::cout << "3.) High scores" << std::endl;
	std::cout << "4.) Exit game" << std::endl;
	std::cout << "==============================" << std::endl;
	std::cout << "Enter a number:";
}

int Menu::AdjustSettings()
{
	if (settings != nullptr)
	{
		delete settings;
		settings = nullptr;
	}

	try
	{
		settings = new Settings();
	}
	catch (ExceedsScreenResolutionException* e)
	{
		std::cerr << e->GetErrorMsg();
		std::string tmp;
		std::cin >> tmp;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int Menu::RunGame(unsigned& totalScore)
{
	WindowHandler* w = nullptr;
	try
	{
		w = new WindowHandler(settings);
	}
	catch (std::exception* e)
	{
		std::cerr << e->what();
		std::string tmp;
		std::cin >> tmp;
		return EXIT_FAILURE;
	}

	if (w != nullptr)
	{
		totalScore += w->Run();
	}
	delete w;
	return EXIT_SUCCESS;
}

int Menu::OpenMenu()
{
	if (settings == nullptr)
	{
		if (AdjustSettings() == EXIT_FAILURE)
		{
			return EXIT_FAILURE;
		}
	}

	HighScores hs;

	while (true)
	{
		unsigned input;
		do
		{
			PrintMenu();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> input;
		} while ((input < 1) && (input > 4));

		switch (input)
		{
		case 1:
		{
			unsigned lives = 5;
			unsigned totalScore = 0;
			while (lives-- > 0 && RunGame(totalScore) == EXIT_SUCCESS)
			{
				std::cout << "Total score: " << totalScore << " Lives remaining: " << lives << std::endl;
			}

			if (hs.IsHighScore(totalScore))
			{
				std::cout << "NEW HIGHSCORE: " << totalScore << std::endl;
				std::cout << "Enter your name: ";

				std::string name;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> name;
				hs.AddHighScore(name, totalScore);
			}

			break;
		}
		case 2:
			if (AdjustSettings() == EXIT_FAILURE)
			{
				return EXIT_FAILURE;
			}
			break;
		case 3:
			hs.PrintHighScores();
			break;
		case 4:
			if (settings != nullptr)
			{
				delete settings;
				settings = nullptr;
			}
			return EXIT_SUCCESS;
		default:
			break;
		}
	}
	return EXIT_FAILURE;
}
