#pragma once
struct Color
{
	float r;
	float g;
	float b;
	Color(float _r, float _g, float _b) :
		r(_r),
		g(_g),
		b(_b)
	{}

	static Color WHITE;
	static Color LGRAY;
	static Color GRAY;
	static Color DGRAY;
	static Color BLACK;
	static Color CYAN;
	static Color RED;
	static Color TEAL;
	static Color MAROON;
	static Color VIOLET;
	static Color LIME;
	static Color PURPLE;
	static Color GREEN;
	static Color YELLOW;
	static Color BLUE;
	static Color OLIVE;
	static Color NAVY;
};