#pragma once

#include "Libs.h"
#include "Clock.h"

enum KEYCODE {
	Q,W,E,R,T,Y,U,I,O,P,A,S,D,F,G,H,J,K,L,Z,X,C,V,B,N,M
};


enum AXIS {
	MouseX, MouseY
};

class InputHandler {
	friend class Window;
public:
	float GetMouseX();
	float GetMouseY();
	float GetAxis(AXIS axis);
	bool IsKeyPress(KEYCODE keycode);
	bool IsKeyHold(KEYCODE keycode);
public:
	InputHandler();
	~InputHandler();
	InputHandler(const InputHandler&) = delete;
	InputHandler& operator = (const InputHandler&) = delete;

private:
	void HandleMouseLeave();
	void HandleMouse(LPARAM lParam, WPARAM wParam);
	void HandleKeyboardDown(LPARAM lParam, WPARAM wParam);
	void HandleKeyboardUp(LPARAM lParam, WPARAM wParam);
	void CalculateMouseAxis();
private:
	std::vector<bool> keystates;
	const static std::unordered_map<int, KEYCODE> keymap;
	float mouseAxisX, mouseAxisY;
	float mouseX, mouseY;
	float premouseX, premouseY;
	float deltaTime;
	float current_time, previous_time;
	POINTS mousePoint;
};
