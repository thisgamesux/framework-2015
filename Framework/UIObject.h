#pragma once

struct UIMouse;

struct UIObject
{
	virtual ~UIObject() {}

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
	virtual void OnDraw(FWSDK::IRenderer* renderer) {}
	virtual bool OnInput(FWSDK::UIMouse* mouse) { return false; }

	FWSDK::UIObject*	parent;
	FWSDK::ColorScheme	scheme;
	FWSDK::Area2D		area;
};