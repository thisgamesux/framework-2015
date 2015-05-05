#pragma once

struct Color
{
	Color() : r(0), g(0), b(0), a(255) {}

	Color(UINT8 r, UINT8 g, UINT8 b, UINT8 a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	UINT8 r, g, b, a;
};
