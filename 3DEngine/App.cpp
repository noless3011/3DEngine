#include "App.h"


App::App() : wnd(800, 600, L"My window") {
	
}


int App::Go() {
	MSG msg = { };
	bool hasMessage = true;
	clock = std::make_unique<Clock>();
	while (true)
	{
		hasMessage = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
		if (msg.message == WM_QUIT) {
			return (int)msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
		Update();
		wnd.Gfx().EndFrame();

	}
	return (int)msg.wParam;
}


void App::Update() {
	
	wnd.ChangeWindowName(std::to_wstring(clock->Now()).c_str());
	wnd.Gfx().Draw(clock->Now());
}