#include "stdafx.h"

void FWSDK::UIWindow::Draw(FWSDK::IRenderer* renderer) {
	renderer->drawRect(this->area.x, this->area.y, this->area.w, this->area.h, FWSDK::Color(255, 0, 0, 255));
}