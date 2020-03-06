#include <cstdlib>
#include <iostream>

#include "GameController.h"
#include "Settings.h"

void GameController::InitBoard()
{
	_board = new Tile*[_columns];
	for (unsigned i = 0; i < _columns; ++i)
	{
		_board[i] = new Tile[_rows];
		for (unsigned j = 0; j < _rows; ++j)
		{
			_board[i][j] = Tile::EMPTY;
		}
	}
}

void GameController::InitPlayer()
{
	unsigned headX = rand() % _columns;
	unsigned headY = rand() % _rows;

	_board[headX][headY] = Tile::HEAD;

	_player.push_back(std::make_pair(headX,headY));

}

void GameController::UpdateScore()
{
	_score = _score + _difficulty * _player.size();
	std::cout << "Current score: " << _score << std::endl;
}

void GameController::PlaceFood()
{
	unsigned foodX, foodY;
	if (_player.size() >= (_rows*_columns))
	{
		_gameState = GameState::VICTORY;
		return;
	}
	do
	{
		foodX = rand() % _columns;
		foodY = rand() % _rows;
	}
	while (_board[foodX][foodY] != Tile::EMPTY);

	_board[foodX][foodY] = Tile::FOOD;
}

void GameController::Propagate(Direction dir)
{
	if (_currentDirection != dir)
	{
		if (_currentDirection == Direction::NONE)
		{
			_currentDirection = dir;
		}
		else if (_currentDirection == Direction::UP)
		{
			if (dir != Direction::DOWN)
			{
				_currentDirection = dir;
			}
		}
		else if (_currentDirection == Direction::DOWN)
		{
			if (dir != Direction::UP)
			{
				_currentDirection = dir;
			}
		}
		else if (_currentDirection == Direction::LEFT)
		{
			if (dir != Direction::RIGHT)
			{
				_currentDirection = dir;
			}
		}
		else if (_currentDirection == Direction::RIGHT)
		{
			if (dir != Direction::LEFT)
			{
				_currentDirection = dir;
			}
		}
	}

	if (_gameState != GameState::PLAYING)
	{
		return;
	}

	_board[_player.front().first][_player.front().second] = Tile::BODY;

	switch (_currentDirection)
	{
	case Direction::UP:
		if (_player.front().second == (_rows - 1))
		{
			_gameState = GameState::DEAD;
		}
		else
		{
			_player.push_front(std::make_pair(_player.front().first, _player.front().second + 1));
		}
		break;
	case Direction::DOWN:
		if (_player.front().second == 0)
		{
			_gameState = GameState::DEAD;
		}
		else
		{
			_player.push_front(std::make_pair(_player.front().first, _player.front().second - 1));
		}
		break;
	case Direction::LEFT:
		if (_player.front().first == 0)
		{
			_gameState = GameState::DEAD;
		}
		else
		{
			_player.push_front(std::make_pair(_player.front().first - 1, _player.front().second));
		}
		break;
	case Direction::RIGHT:
		if (_player.front().first == (_columns - 1))
		{
			_gameState = GameState::DEAD;
		}
		else
		{
			_player.push_front(std::make_pair(_player.front().first + 1, _player.front().second));
		}
		break;
	case Direction::NONE:
		break;
	default:
		break;
	}

	if (_gameState == GameState::PLAYING && _currentDirection != Direction::NONE)
	{
		bool eaten = false;
		/////
		if (_board[_player.front().first][_player.front().second] == Tile::FOOD)
		{
			eaten = true;
		}
		bool tail = false;
		if (_player.front().first == _player.back().first && _player.front().second == _player.back().second)
		{
			tail = true;
		}

		if (_board[_player.front().first][_player.front().second] == Tile::BODY && !tail)
		{
			_gameState = GameState::DEAD;
			return;
		}
		_board[_player.front().first][_player.front().second] = Tile::HEAD;

		if (eaten)
		{
			UpdateScore();
			PlaceFood();
		}
		else
		{
			if (!tail)
			{
				_board[_player.back().first][_player.back().second] = Tile::EMPTY;
			}
			_player.pop_back();
		}
		
	}
}


GameController::GameController(Settings* s)
{
	_rows = s->rows;
	_columns = s->columns;

	_difficulty = s->difficulty;
	_score = 0;

	InitBoard();
	InitPlayer();
	PlaceFood();
	_gameState = GameState::PLAYING;
}


GameController::~GameController()
{
	for (unsigned i = 0; i < _rows; ++i)
	{
		delete _board[i];
	}
	delete _board;
}

Tile** GameController::GetBoard() const
{
	return _board;
}
