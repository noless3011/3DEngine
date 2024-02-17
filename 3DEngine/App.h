#pragma once
#include "Libs.h"
#include "Window.h"


class App {
public:
	App();
	int Go();
	void Update();
private:
	Window wnd;
};