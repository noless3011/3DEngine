#pragma once
#include "Window.h"
#include "Graphics.h"
#include "Clock.h"

class App {
public:
	static App& GetInstance(unsigned int x = 0, unsigned int y = 0) {
		static App instance(x, y);
		return instance;
	}

	App(const App&) = delete;
	App& operator=(const App&) = delete;

	int Go();
	void Start();
	void Update();
	std::shared_ptr<Window> getWindow();
private:
	App();
	App(unsigned int x, unsigned int y);

	unsigned int width, height;
	std::shared_ptr<Window> pWnd;
};