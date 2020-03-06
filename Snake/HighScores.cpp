#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include "HighScores.h"

bool HighScores::compare(const hsEntry& first, const hsEntry& second)
{
	return first.second > second.second;
}

HighScores::HighScores()
{
	std::ifstream f("highscores.txt");

	if (f.good())
	{
		char line[50];
		while (f.getline(line,50,'\n'))
		{
			std::string l(line);
			std::string score = l.substr(0, l.find_first_of("|"));
			std::string player = l.substr(l.find_first_of("|") + 1);
			_highScores.push_back(std::make_pair(player, std::stoi(score)));
		}
		f.close();
	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{
			_highScores.push_back(std::make_pair("Anonymus", i));
		}
	}

	_highScores.sort(compare);
}

HighScores::~HighScores()
{
	std::ofstream f("highscores.txt");
	for (auto hs : _highScores)
	{
		f << hs.second << "|" << hs.first << std::endl;
	}
	f.close();
}


bool HighScores::IsHighScore(unsigned highScore)
{
	return (_highScores.back().second < highScore);
}

void HighScores::AddHighScore(std::string player, unsigned highScore)
{
	_highScores.push_back(std::make_pair(player.substr(0,10), highScore));
	_highScores.sort(compare);
	while (_highScores.size() > 10)
	{
		_highScores.pop_back();
	}
}

void HighScores::PrintHighScores()
{
	std::cout << "High scores:" << std::endl;
	for (auto hs : _highScores)
	{
		std::stringstream ss;
		ss << std::setw(12) << hs.first  << " " << std::setw(7) << hs.second << std::endl;
		std::cout << ss.str();
	}
}