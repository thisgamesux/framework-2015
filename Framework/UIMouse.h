#pragma once

enum UIMouseClickState
{
	LEFT,
	RIGHT,
	MIDDLE
};

struct UIMouseClickStateData
{
	bool clicked;
	bool held;
	std::chrono::milliseconds::rep lastClick;
};

struct UIMouse : public FWSDK::UIObject
{
	UIMouse() {
		area.x = area.y = 0;
		area.w = area.h = 1;

		for (auto &state : states) {
			state.clicked = state.held = false;
			state.lastClick = 0;
		}
	}

	virtual void OnDraw(FWSDK::IRenderer* renderer) 
	{
		renderer->drawRect(area.x - 1, area.y - 1, 1, 12, scheme.outline);
		renderer->drawRect(area.x, area.y - 1, 1, 1, scheme.outline);
		renderer->drawRect(area.x, area.y, 1, 10, scheme.front);
		renderer->drawRect(area.x, area.y + 10, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 1, area.y, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 1, area.y + 1, 1, 8, scheme.front);
		renderer->drawRect(area.x + 1, area.y + 9, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 2, area.y + 1, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 2, area.y + 2, 1, 6, scheme.front);
		renderer->drawRect(area.x + 2, area.y + 8, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 3, area.y + 2, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 3, area.y + 3, 1, 6, scheme.front);
		renderer->drawRect(area.x + 3, area.y + 9, 1, 2, scheme.outline);
		renderer->drawRect(area.x + 4, area.y + 3, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 4, area.y + 4, 1, 7, scheme.front);
		renderer->drawRect(area.x + 4, area.y + 11, 1, 2, scheme.outline);
		renderer->drawRect(area.x + 5, area.y + 4, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 5, area.y + 5, 1, 2, scheme.front);
		renderer->drawRect(area.x + 5, area.y + 7, 1, 2, scheme.outline);
		renderer->drawRect(area.x + 5, area.y + 9, 1, 4, scheme.front);
		renderer->drawRect(area.x + 5, area.y + 13, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 6, area.y + 5, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 6, area.y + 6, 1, 1, scheme.front);
		renderer->drawRect(area.x + 6, area.y + 7, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 6, area.y + 9, 1, 2, scheme.outline);
		renderer->drawRect(area.x + 6, area.y + 11, 1, 2, scheme.front);
		renderer->drawRect(area.x + 6, area.y + 13, 1, 1, scheme.outline);
		renderer->drawRect(area.x + 7, area.y + 6, 1, 2, scheme.outline);
		renderer->drawRect(area.x + 7, area.y + 11, 1, 2, scheme.outline);
	}

	bool insideObject(FWSDK::UIObject* obj) {
		return (obj->area.containsPoint(FWSDK::Vec2D(this->area.x, this->area.y)));
	}

	FWSDK::UIMouseClickStateData states[3];
};