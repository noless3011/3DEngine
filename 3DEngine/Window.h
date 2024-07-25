#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Event.h"
#include "EventDispatcher.h"
#include "EventListener.h"
#include "Input.h"

class Window {
public:
	Window(int width, int height, std::wstring windowName);
	~Window();
	Graphics& Gfx();
	InputHandler& Input();
	void ChangeWindowName(LPCWSTR string);
	static std::optional<int> ProcessMessage();
	template<typename T>
	void AddListener(std::unique_ptr<EventListener<T>>& listener);
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
	static std::shared_ptr<EventDispatcher> eventDispatcher;
	HWND hWnd;
	int width, height;
};

template<typename T>
inline void Window::AddListener(std::unique_ptr<EventListener<T>>& listener)
{
	eventDispatcher->AddEventListener(std::move(listener));
}
