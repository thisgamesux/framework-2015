#pragma once

struct UIMouseClickStateData
{
	bool clicked;
	bool held;
	DWORD lastClick;

	void Click() {
		clicked = held = true;
		lastClick = GetTickCount();
	}

	void Clear() {
		clicked = held = false;
		lastClick = NULL;
	}
};

struct UIMouseDragData
{
	bool dragging;
	FWSDK::UIWindow* window;
	int windowXOffset;
	int windowYOffset;
};

struct UIMouse : public FWSDK::UIObject
{
	virtual void Draw(FWSDK::IRenderer* renderer) 
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

	void ClearStates() {
		leftState.Clear();
		rightState.Clear();
	}

	void ClearClickStates() {
		leftState.clicked = rightState.clicked = false;
	}

	virtual void Input(WPARAM wParam, LPARAM lParam, UINT msg)
	{
		switch (msg)
		{
			case WM_LBUTTONDOWN:
			leftState.Click();
			break;
			case WM_LBUTTONUP:
			leftState.held = false;
			break;
			case WM_RBUTTONDOWN:
			rightState.Click();
			break;
			case WM_RBUTTONUP:
			rightState.held = false;
			break;
		}
	}

	FWSDK::UIMouseClickStateData leftState;
	FWSDK::UIMouseClickStateData rightState;
	FWSDK::UIMouseDragData dragState;

	bool drawMouseDebugInfo;
};