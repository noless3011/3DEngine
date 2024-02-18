#pragma once
#include "Libs.h"
#include "Graphics.h"

class Window {
public:
	Window(int width, int height, std::wstring windowName);
	~Window();
	Graphics& Gfx();
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
	HWND hWnd;
	int width, height;
};