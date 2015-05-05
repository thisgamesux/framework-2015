#pragma once

class IRenderer
{
public:
	virtual void drawRect(int x, int y, int w, int h, FWSDK::Color color) = 0;
	virtual void drawString(int x, int y, std::string text, FWSDK::Color color) = 0;

	void drawShadedOutlineRect(int x, int y, int w, int h, FWSDK::Color color1, FWSDK::Color color2);
	void drawOutlineRect(int x, int y, int w, int h, FWSDK::Color color);
	void drawRoundedOutlineRect(int x, int y, int w, int h, FWSDK::Color color);
	void drawRoundedRect(int x, int y, int w, int h, FWSDK::Color color);
	void drawGradientRect(int x, int y, int w, int h, FWSDK::Color start, FWSDK::Color end);
	void drawSmallerLine(int x, int y, int w, int smaller, FWSDK::Color color);
};