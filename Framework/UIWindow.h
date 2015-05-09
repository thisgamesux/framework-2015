#pragma once

struct UIWindow : public FWSDK::UIObject
{
	std::vector<FWSDK::UIObject*> objects;
	std::string title;

	// Set to true to always render this window
	bool drawWhenInactive;

	//
	virtual void OnDraw(FWSDK::IRenderer* renderer);
	virtual bool OnInput(FWSDK::UIMouse* mouse);
};