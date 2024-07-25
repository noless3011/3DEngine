#pragma once

#include "Clock.h"
#include "Event.h"
#include "EventDispatcher.h"
#include "EventListener.h"

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
	InputHandler(std::shared_ptr<EventDispatcher> dispatcher);
	~InputHandler();
	InputHandler(const InputHandler&) = delete;
	InputHandler& operator = (const InputHandler&) = delete;

private:
	void HandleMouseLeave();
	void HandleMouseStop();
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
	std::shared_ptr <EventDispatcher> dispatcher;
};
