#pragma once
#include <list>

class HighScores
{
	typedef std::pair<std::string, unsigned> hsEntry;
	std::list<hsEntry> _highScores;

	static bool compare(const hsEntry& first, const hsEntry& second);
public:
	HighScores();
	~HighScores();

	bool IsHighScore(unsigned highScore);
	void AddHighScore(std::string player, unsigned highScore);
	void PrintHighScores();
};

