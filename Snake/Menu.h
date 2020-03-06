#pragma once

struct Settings;

class Menu
{
private:
	Menu() {}
	~Menu() {}

	static void PrintMenu();
	static int AdjustSettings();
	static Settings* settings;
	static int RunGame(unsigned& totalScore);
public:
	static int OpenMenu();
};

