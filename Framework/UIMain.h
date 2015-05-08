#pragma once

struct UIMainObject : public FWSDK::UIObject
{
	std::list<FWSDK::UIWindow*> windows;

	FWSDK::UIMouse* mouse;

	bool active;

	UIMainObject() {
		mouse = new FWSDK::UIMouse();
		active = false;
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
			if (window->area.isPosInWindowArea(x, y)) {
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
				pCurrent->Delete();
				windows.erase(i);
				delete pCurrent; // Hope this works?
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

	virtual void Draw(FWSDK::IRenderer* renderer);
	virtual void Input(WPARAM wParam, LPARAM lParam, UINT msg);

	virtual void Delete() {
		delete mouse;
	}
};