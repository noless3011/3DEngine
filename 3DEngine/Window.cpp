#include "stdafx.h"
#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;

std::shared_ptr<EventDispatcher> Window::eventDispatcher = std::make_shared<EventDispatcher>();
std::unique_ptr<InputHandler> Window::pInputHandler = std::make_unique<InputHandler>(Window::eventDispatcher);

HINSTANCE Window::WindowClass::GetInstance()
{
	return wndClass.hInstance;
}

const wchar_t* Window::WindowClass::GetWindowClassName()
{
	return wndClass.className;
}

Window::WindowClass::WindowClass() : hInstance(GetModuleHandle(nullptr))
{
	WNDCLASS wc = {};
	wc.lpszClassName = className;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;

	RegisterClass(&wc);
}

Window::WindowClass::~WindowClass()
{
}

Window::Window(int width, int height, std::wstring windowName)
{
	Window::width = width;
	Window::height = height;
	LPCWSTR thisWindowName = windowName.c_str();
	hWnd = CreateWindowEx(
		0, WindowClass::GetWindowClassName(), thisWindowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		nullptr, nullptr, WindowClass::GetInstance(), nullptr
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	pGfx = std::make_unique<Graphics>(hWnd, width, height);
}

Window::~Window()
{
}

Graphics& Window::Gfx()
{
	return *pGfx;
}

InputHandler& Window::Input()
{
	return *pInputHandler;
}

void Window::ChangeWindowName(LPCWSTR string)
{
	SetWindowText(hWnd, string);
}

std::optional<int> Window::ProcessMessage()
{
	MSG msg = { };
	bool hasMessage = true;
	while (true)
	{
		hasMessage = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
		if (msg.message == WM_QUIT) {
			return (int)msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CLOSE: {
		PostQuitMessage(0);
		return 0;
	}
	case WM_MOUSELEAVE:
		pInputHandler->HandleMouseLeave();
		break;
	case WM_MOUSEMOVE: {
		pInputHandler->HandleMouse(lParam, wParam);
		break;
	}
	case WM_KEYDOWN: {
		pInputHandler->HandleKeyboardDown(lParam, wParam);
		break;
	}
	case WM_KEYUP: {
		pInputHandler->HandleKeyboardUp(lParam, wParam);
		break;
	}
	}
	pInputHandler->HandleMouseStop();

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}