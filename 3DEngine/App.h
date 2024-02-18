#pragma once
#include "Libs.h"
#include "Window.h"
#include "Graphics.h"
#include "Clock.h"


class App {
public:
	App();
	int Go();
	void Start();
	void Update();
private:
	Window wnd;
	std::unique_ptr<Clock> clock;
};