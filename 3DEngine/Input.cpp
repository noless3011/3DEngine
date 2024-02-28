#include "Input.h"

const std::unordered_map<int, KEYCODE> InputHandler::keymap = {
	{0x41, A},
	{0x42, B},
	{0x43, C},
	{0x44, D},
	{0x45, E},
	{0x46, F},
	{0x47, G},
	{0x48, H},
	{0x49, I},
	{0x4A, J},
	{0x4B, K},
	{0x4C, L},
	{0x4D, M},
	{0x4E, N},
	{0x4F, O},
	{0x50, P},
	{0x51, Q},
	{0x52, R},
	{0x53, S},
	{0x54, T},
	{0x55, U},
	{0x56, V},
	{0x57, W},
	{0x58, X},
	{0x59, Y},
	{0x5A, Z}

};


InputHandler::InputHandler()
{
	keystates = std::vector<bool>(26, false);
	mouseX = 0;
	mouseY = 0;
	mouseAxisX = 0;
	mouseAxisY = 0;
	premouseX = mouseX;
	premouseY = mouseY;
	current_time = 0.1;
	previous_time = 0;
}

InputHandler::~InputHandler()
{
}


float InputHandler::GetMouseX()
{
	return mouseX;
}

float InputHandler::GetMouseY()
{
	return mouseY;
}

float InputHandler::GetAxis(AXIS axis)
{
	switch (axis)
	{
	case MouseX:
		
		return mouseAxisX;
		break;
	case MouseY:
		return mouseAxisY;
		break;
	default:
		break;
	}
}
//this function only return true once, this function is temporarely unfinished
bool InputHandler::IsKeyPress(KEYCODE keycode)
{
	return keystates[keycode];
}

bool InputHandler::IsKeyHold(KEYCODE keycode)
{
	return keystates[keycode];
}



void InputHandler::HandleMouseLeave()
{
	mouseAxisX = 0;
	mouseAxisY = 0;
}

void InputHandler::HandleMouse(LPARAM lParam, WPARAM wParam)
{
	previous_time = current_time;
	current_time = Clock::Now();
	deltaTime = current_time - previous_time;

	CalculateMouseAxis();


	mousePoint = MAKEPOINTS(lParam);
	premouseX = mouseX;
	premouseY = mouseY;
	mouseX = mousePoint.x / static_cast<float>(800);
	mouseY = mousePoint.y / static_cast<float>(600);
}

void InputHandler::HandleKeyboardDown(LPARAM lParam, WPARAM wParam)
{
	if (keymap.contains(wParam)) {
		keystates[keymap.at(wParam)] = true;
	}
}

void InputHandler::HandleKeyboardUp(LPARAM lParam, WPARAM wParam)
{
	if (keymap.contains(wParam)) {
		keystates[keymap.at(wParam)] = false;
	}
	
}

void InputHandler::CalculateMouseAxis()
{
	float d = mouseX - premouseX;
	if (d > 0.001f || d < -0.001f) {
		mouseAxisX = (mouseX - premouseX) / deltaTime;
	}
	else {
		mouseAxisX = 0;
	}
	d = mouseY - premouseY;
	if (d > 0.001f || d < -0.001f) {
		mouseAxisY = (mouseY - premouseY) / deltaTime;
	}
	else {
		mouseAxisY = 0;
	}
	
}
