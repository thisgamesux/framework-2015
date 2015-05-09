#pragma once

typedef char int8;
static_assert(sizeof(int8) == 1, "int8 size must be 1 byte.");

typedef unsigned char uint8;
static_assert(sizeof(uint8) == 1, "uint8 size must be 1 byte.");

typedef short int16;
static_assert(sizeof(int16) == 2, "int16 size must be 2 bytes.");

typedef unsigned short uint16;
static_assert(sizeof(uint16) == 2, "uint16 size must be 2 bytes.");

typedef int int32;
static_assert(sizeof(int32) == 4, "int32 size must be 4 bytes.");

//Fixes compilation problem under xcode
#ifndef _UINT32
#define _UINT32
typedef unsigned int uint32;
#endif

static_assert(sizeof(uint32) == 4, "uint32 size must be 4 bytes.");

typedef long long int64;
static_assert(sizeof(int64) == 8, "int64 size must be 8 bytes.");

typedef unsigned long long uint64;
static_assert(sizeof(uint64) == 8, "uint64 size must be 8 bytes.");

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

	uint32 r, g, b, a;
};

static_assert(sizeof(FWSDK::Color) == 16, "FWSDK::Color expected 16 bytes");

struct ColorScheme
{
	FWSDK::Color back, front, outline;
};

static_assert(sizeof(FWSDK::ColorScheme) == 48, "FWSDK::ColorScheme expected 48 bytes");

struct Vec2D
{
	Vec2D(void){}
	Vec2D(uint32 x, uint32 y) : x(x), y(y) {}

	uint32 x, y;
};

static_assert(sizeof(FWSDK::Vec2D) == 8, "FWSDK::Vec2D expected 8 bytes");

struct Area2D
{
	Area2D(void){}
	Area2D(uint32 x, uint32 y, uint32 w, uint32 h) : x(x), y(y), w(w), h(h) {}

	uint32 left(){ return x; }
	uint32 right(){ return x + w; }
	uint32 top(){ return y; }
	uint32 bottom(){ return y + h; }

	bool containsPoint(FWSDK::Vec2D vec)
	{
		return (vec.x >= left() && vec.x <= right() && vec.y >= top() && vec.y <= bottom());
	}

	uint32 x, y, w, h;
};

static_assert(sizeof(FWSDK::Area2D) == 16, "FWSDK::Area2D expected 16 bytes");