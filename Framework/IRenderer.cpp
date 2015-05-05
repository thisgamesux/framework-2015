#include "stdafx.h"

void FWSDK::IRenderer::drawShadedOutlineRect(int x, int y, int w, int h, FWSDK::Color color1, FWSDK::Color color2)
{
	drawRect(x, y, w, 1, color1);
	drawRect(x, y, 1, h, color1);
	drawRect(x + 1, y + h - 1, w - 1, 1, color2);
	drawRect(x + w - 1, y + 1, 1, h - 1, color2);
}

void FWSDK::IRenderer::drawOutlineRect(int x, int y, int w, int h, FWSDK::Color color)
{
	drawShadedOutlineRect(x, y, w, h, color, color);
}

void FWSDK::IRenderer::drawRoundedOutlineRect(int x, int y, int w, int h, FWSDK::Color color)
{
	//
}

void FWSDK::IRenderer::drawRoundedRect(int x, int y, int w, int h, FWSDK::Color color)
{
	drawSmallerLine(x, y, w, 4, color);
	drawSmallerLine(x, y + 1, w, 2, color);
	drawSmallerLine(x, y + 2, w, 1, color);
	drawSmallerLine(x, y + 3, w, 1, color);
	drawRect(x, y + 4, w, h - 4, color);
	drawSmallerLine(x, y + h, w, 1, color);
	drawSmallerLine(x, y + h + 1, w, 1, color);
	drawSmallerLine(x, y + h + 2, w, 2, color);
	drawSmallerLine(x, y + h + 3, w, 4, color);
}

void FWSDK::IRenderer::drawGradientRect(int x, int y, int w, int h, FWSDK::Color start, FWSDK::Color end)
{
	float rDif = ((float)end.r - (float)start.r) / h;
	float gDif = ((float)end.g - (float)start.g) / h;
	float bDif = ((float)end.b - (float)start.b) / h;
	float aDif = ((float)end.a - (float)start.a) / h;

	for (int i = 0; i < h; i++)
	{
		drawRect(x, y + i, w, 1,
			Color(
			start.r + (int)(rDif * i),
			start.g + (int)(gDif * i),
			start.b + (int)(bDif * i),
			start.a + (int)(aDif * i)));
	}
}

void FWSDK::IRenderer::drawSmallerLine(int x, int y, int w, int smaller, FWSDK::Color color)
{
	x += smaller;

	w -= (smaller * 2);

	drawRect(x, y, w, 1, color);
}