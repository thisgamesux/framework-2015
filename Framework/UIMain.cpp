#include "stdafx.h"

void FWSDK::UIMainObject::Draw(FWSDK::IRenderer* renderer) {
	for (auto window : windows) {
		window->Draw(renderer);
	}
}

void FWSDK::UIMainObject::Input(WPARAM wParam, LPARAM lParam, UINT msg) {
	for (auto window : windows) {
		window->Input(wParam, lParam, msg);
	}
}