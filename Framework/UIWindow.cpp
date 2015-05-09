#include "stdafx.h"

void FWSDK::UIWindow::OnDraw(FWSDK::IRenderer* renderer) {
	renderer->drawRect(this->area.x, this->area.y, this->area.w, this->area.h, this->scheme.front);
}

bool FWSDK::UIWindow::OnInput(FWSDK::UIMouse* mouse, FWSDK::UIKeyboard* keyboard) {
	if (mouse->insideObject(this)) {
		this->scheme.front = FWSDK::Color(0, 0, 255, 255);
	}
	else {
		this->scheme.front = FWSDK::Color(255, 0, 0, 255);
	}

	return false;
}