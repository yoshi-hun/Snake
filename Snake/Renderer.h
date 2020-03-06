#pragma once
#include <GLFW/glfw3.h>

#include "Tile.h"
#include "Color.h"

struct Settings;

class Renderer
{
public:
	Renderer(Settings* s);
	~Renderer();

	void Render(Tile** board);

private:

	void DrawRectangle(float x1, float y1, float x2, float y2, Color c);
	void DrawSquare(unsigned x, unsigned y, Tile type);

	void DrawBorders();
	void DrawGrid();

	
	unsigned _rows;
	unsigned _columns;
	unsigned _squareDimension;
	unsigned _padding;
	unsigned _border;
	unsigned _width;
	unsigned _height;

	float borderWidth;
	float borderHeight;
	float paddingWidth;
	float paddingHeight;
	float tileWidth;
	float tileHeight;

};

