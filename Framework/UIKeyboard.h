#pragma once

struct UIKeyState
{
	bool down;
	bool previous;
};

struct UIKeyboard
{
	UIKeyboard() {
		for (auto &state : states) {
			state.down = state.previous = false;
		}
	}

	UIKeyState states[0xFF];
};