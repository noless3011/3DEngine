#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Input.h"

class Window {
public:
	Window(int width, int height, std::wstring windowName);
	~Window();
	Graphics& Gfx();
	InputHandler& Input();
	void ChangeWindowName(LPCWSTR string);
	static std::optional<int> ProcessMessage();
private:
	class WindowClass {
	public:
		static HINSTANCE GetInstance();
		static const wchar_t* GetWindowClassName();
	private:
		static WindowClass wndClass;
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator = (const WindowClass&) = delete;
		static constexpr wchar_t className[] = L"MyWindowClassName";
		HINSTANCE hInstance;
	};
private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	std::unique_ptr<Graphics> pGfx;
	static std::unique_ptr<InputHandler> pInputHandler;
	HWND hWnd;
	int width, height;
};