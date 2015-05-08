#pragma once

struct Color
{
	// Constructors
	Color() : r(0), g(0), b(0), a(255) {}

	Color(UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha) : r(red), g(green), b(blue), a(alpha) {}

	// Member functions
	Color Darker(WORD var);
	Color Lighter(WORD var);

	// Static functions
	void GetHLS(WORD &hue, WORD &lum, WORD &sat, UINT32 &alpha);
	
	static Color GetFromHLS(WORD hue, WORD lum, WORD sat, UINT32 alpha);
	static WORD HueToRGB(WORD n1, WORD n2, WORD hue);

	UINT32 r, g, b, a;
};

struct ColorScheme
{
	FWSDK::Color back, front, outline;
};

struct Area2D
{
	Area2D(void){}
	Area2D(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	int left(){ return x; }
	int right(){ return x + w; }
	int top(){ return y; }
	int bottom(){ return y + h; }

	bool isPosInWindowArea(int xx, int yy)
	{
		return (xx >= left() && xx <= right() && yy >= top() && yy <= bottom());
	}

	int x, y, w, h;
};