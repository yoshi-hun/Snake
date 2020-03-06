#pragma once
#include <list>

#include "Direction.h"
#include "Tile.h"
#include "GameState.h"

struct Settings;

class GameController
{
public:

	GameController(Settings* s);
	~GameController();
	Tile** GetBoard() const;

	void PlaceFood();
	void Propagate(Direction dir);

	unsigned long GetScore() const { return _score; }

	GameState GetState() const { return _gameState; }

private:

	void InitBoard();
	void InitPlayer();

	void UpdateScore();

	unsigned _rows;
	unsigned _columns;

	unsigned _difficulty;
	unsigned _score;

	typedef std::pair<unsigned, unsigned> coord;
	std::list<coord> _player;

	Tile ** _board;

	Direction _currentDirection;
	GameState _gameState;
};

