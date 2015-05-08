#pragma once

struct UIWindow : public FWSDK::UIObject
{
	std::vector<FWSDK::UIObject*> objects;
	std::string title;

	// Set to true to always render this window
	bool drawWhenInactive;

	virtual void Draw(FWSDK::IRenderer* renderer);
};