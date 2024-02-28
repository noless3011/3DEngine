#pragma once
#include "Libs.h"
#include "Window.h"
#include "Graphics.h"
#include "Clock.h"



class App {
public:
	App();
	App(unsigned int x, unsigned int y);
	int Go();
	void Start();
	void Update();
private:
	unsigned int width, height;
	Window wnd;
};