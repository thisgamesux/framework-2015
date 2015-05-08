#pragma once

struct UIObject
{
	virtual void Size(int w, int h)
	{
		this->area.w = w;
		this->area.h = h;
	}

	virtual void Move(int x, int y)
	{
		this->area.x = x;
		this->area.y = y;
	}

	// Undefined
	virtual void Draw(FWSDK::IRenderer* renderer) {}
	virtual void Input(WPARAM wParam, LPARAM lParam, UINT msg) {}
	virtual void Delete() {}

	FWSDK::UIObject*	parent;
	FWSDK::ColorScheme	scheme;
	FWSDK::Area2D		area;
};