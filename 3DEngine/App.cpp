#include "App.h"


App::App() : wnd(800, 600, L"My window") {
	
}

void App::Update() {
	wnd.Gfx().Draw();
}

int App::Go() {
	MSG msg = { };
	bool hasMessage = true;
	while (true)
	{
		hasMessage = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
		if (hasMessage) {
			if (msg.message == WM_QUIT) {
				return (int)msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			Update();
			wnd.Gfx().EndFrame();
		}
		else {
			WaitMessage();
		}

	}
	return (int)msg.wParam;
}