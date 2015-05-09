#include "stdafx.h"

void FWSDK::UIMainObject::OnDraw(FWSDK::IRenderer* renderer) {

	for (auto window : windows) {
		window->OnDraw(renderer);
	}

	// Draw the mouse over all other objects
	mouse->OnDraw(renderer);

#ifdef _DEBUG
	// Draw debug mouse info...
	std::stringstream ss;

	ss << "[X] = " << mouse->area.x << " :: [Y] = " << mouse->area.y <<
		" [LEFT] = " << mouse->states[LEFT].clicked << "::" << mouse->states[LEFT].held << "::" << mouse->states[LEFT].lastClick <<
		" [RIGHT] = " << mouse->states[RIGHT].clicked << "::" << mouse->states[RIGHT].held << "::" << mouse->states[RIGHT].lastClick;

	renderer->drawString(10, 10, ss.str(), FWSDK::Color(255, 255, 255, 255));
#endif
}

// Click/key states are set here, and they apply for the current frame
// The only exception to this is "held", which is unset only when the key up message is obtained
bool FWSDK::UIMainObject::Input(WPARAM wParam, LPARAM lParam, UINT msg) {
	auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	switch (msg) {
	case WM_LBUTTONDOWN:
		mouse->area.x = GET_X_LPARAM(lParam);
		mouse->area.y = GET_Y_LPARAM(lParam);
		mouse->states[LEFT].clicked = mouse->states[LEFT].held = true;
		mouse->states[LEFT].lastClick = currentTime;
		break;
	case WM_LBUTTONUP:
		mouse->states[LEFT].held = false;
		break;
	case WM_RBUTTONDOWN:
		mouse->area.x = GET_X_LPARAM(lParam);
		mouse->area.y = GET_Y_LPARAM(lParam);
		mouse->states[RIGHT].clicked = mouse->states[RIGHT].held = true;
		mouse->states[RIGHT].lastClick = currentTime;
		break;
	case WM_RBUTTONUP:
		mouse->states[RIGHT].held = false;
		break;
	case WM_MBUTTONDOWN:
		mouse->area.x = GET_X_LPARAM(lParam);
		mouse->area.y = GET_Y_LPARAM(lParam);
		mouse->states[MIDDLE].clicked = mouse->states[MIDDLE].held = true;
		mouse->states[MIDDLE].lastClick = currentTime;
		break;
	case WM_MBUTTONUP:
		mouse->states[MIDDLE].held = false;
		break;
	case WM_MOUSEMOVE:
		mouse->area.x = GET_X_LPARAM(lParam);
		mouse->area.y = GET_Y_LPARAM(lParam);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		keyboard->states[wParam].down = true;
		keyboard->states[wParam].previous = ((lParam & (1 << 30)) == 1);
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		keyboard->states[wParam].down = false;
		keyboard->states[wParam].previous = true; // always true here
		break;
	default:
		return false;
	}

	for (auto window : windows) {
		if (window->OnInput(mouse)) {
			break;
		}
	}

	for (auto &state : mouse->states) {
		state.clicked = false;
	}

	return false;
}