#pragma once

struct UIMainObject : public FWSDK::UIObject
{
	std::list<FWSDK::UIWindow*> windows;

	FWSDK::UIMouse* mouse;
	FWSDK::UIKeyboard* keyboard;

	bool active;

	UIMainObject() {
		// Set default mouse data
		mouse = new FWSDK::UIMouse();
		mouse->parent = this;
		mouse->scheme.front = FWSDK::Color(255, 255, 255, 255);

		keyboard = new FWSDK::UIKeyboard();

		active = false;
	}

	virtual ~UIMainObject() {
		delete mouse;
	}

	// Add window, return pointer
	FWSDK::UIWindow* AddWindow(std::string title, FWSDK::Area2D area, bool drawWhenInactive = false) {
		FWSDK::UIWindow* pNewWindow = new FWSDK::UIWindow();

		pNewWindow->title = title;
		pNewWindow->area = area;
		pNewWindow->drawWhenInactive = drawWhenInactive;
		pNewWindow->parent = this;

		windows.push_back(pNewWindow);

		return pNewWindow;
	}

	// Find window by title
	FWSDK::UIWindow* FindWindow(std::string title) {
		for (auto window : windows) {
			if (window->title.compare(title) == 0) {
				return window;
			}
		}

		return nullptr;
	}

	FWSDK::UIWindow* GetTopmostWindowAtPosition(int x, int y) {
		for (auto window : windows) {
			if (window->area.containsPoint(FWSDK::Vec2D(x, y))) {
				return window;
			}
		}

		return nullptr;
	}

	// Delete window by pointer
	void DeleteWindow(FWSDK::UIWindow* window) {
		if (!window)
			return;

		for (auto i = windows.begin(); i != windows.end(); ++i) {
			FWSDK::UIWindow* pCurrent = (*i);

			if (pCurrent == window) {
				windows.erase(i);
				delete pCurrent;
				break;
			}
		}
	}

	FWSDK::UIWindow* MoveToFront(std::list<FWSDK::UIWindow*>::iterator i) {
		if (i == windows.begin())
			return (*i);

		windows.push_front(*i);
		windows.erase(i);

		return windows.front();
	}

	bool Input(WPARAM wParam, LPARAM lParam, UINT msg);

	//
	virtual void OnDraw(FWSDK::IRenderer* renderer);
};