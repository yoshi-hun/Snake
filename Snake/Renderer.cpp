#include <iostream>

#include "Renderer.h"
#include "Settings.h"

void Renderer::Render(Tile** board)
{
	DrawBorders();
	DrawGrid();
	for (unsigned i = 0; i < _columns; ++i)
	{
		for (unsigned j = 0; j < _rows; ++j)
		{
			DrawSquare(i, j, board[i][j]);
		}
	}
}


void Renderer::DrawBorders()
{

	DrawRectangle(
		-1.0f,
		1.0f,
		1.0f,
		1.0f - borderHeight,
		Color::MAROON);

	DrawRectangle(
		-1.0f,
		1.0f - borderHeight,
		-1.0f + borderWidth,
		-1.0f + borderHeight,
		Color::MAROON);


	DrawRectangle(
		1.0f - borderWidth,
		1.0f - borderHeight,
		1.0f,
		-1.0f + borderHeight,
		Color::MAROON);


	DrawRectangle(
		-1.0f,
		-1.0f + borderHeight,
		1.0f,
		-1.0f,
		Color::MAROON);

}

void Renderer::DrawGrid()
{

	for (unsigned i = 1; i < _rows; ++i)
	{
		DrawRectangle(
			-1.0f + borderWidth,
			-1.0f + borderHeight + i * (tileHeight + paddingHeight),
			1.0f - borderWidth,
			-1.0f + borderHeight + i * (tileHeight + paddingHeight) - paddingHeight,
			Color::DGRAY
		);
	}

	for (unsigned i = 1; i < _columns; ++i)
	{
		DrawRectangle(
			-1.0f + borderWidth + i * (tileWidth + paddingWidth),
			-1.0f + borderHeight,
			-1.0f + borderWidth + i * (tileWidth + paddingWidth) - paddingWidth,
			1.0f - borderHeight,
			Color::DGRAY
		);
	}
}


Renderer::Renderer(Settings* s)
{
	_rows = s->rows;
	_columns = s->columns;
	_squareDimension = s->squareDimension;
	_padding = s->padding;
	_border = s->border;
	_width = s->width;
	_height = s->height;

	//Dimensions are [-1;1]
	borderWidth = _border * 2 / (float)_width;
	borderHeight = _border * 2 / (float)_height;

	paddingWidth = _padding * 2 / (float)_width;
	paddingHeight = _padding * 2 / (float)_height;

	tileWidth = _squareDimension * 2 / (float)_width;
	tileHeight = _squareDimension * 2 / (float)_height;
}


void Renderer::DrawRectangle(float x1, float y1, float x2, float y2, Color c)
{
	glBegin(GL_QUADS);
	glColor3f(c.r, c.g, c.b);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}

void Renderer::DrawSquare(unsigned x, unsigned y, Tile type)
{
	Color c = Color::BLACK;
	switch (type)
	{
	case Tile::EMPTY:
		break;
	case Tile::BODY:
		c = Color::GREEN;
		break;
	case Tile::FOOD:
		c = Color::NAVY;
		break;
	case Tile::HEAD:
		c = Color::LIME;
	default:
		break;
	}
	DrawRectangle(
		-1.0f + borderWidth + x * (tileWidth + paddingWidth),
		-1.0f + borderHeight + y * (tileHeight + paddingHeight),
		-1.0f + borderWidth + x * (tileWidth + paddingWidth) + tileWidth,
		-1.0f + borderHeight + y * (tileHeight + paddingHeight) + tileHeight,
		c
	);
}


Renderer::~Renderer()
{
}
