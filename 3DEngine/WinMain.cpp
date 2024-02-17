#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
	const wchar_t CLASS_NAME[] = L"This is a class name";
	WNDCLASS wc = {};
	wc.lpszClassName = CLASS_NAME;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;

	RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(
		0, CLASS_NAME, L"A window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, hInstance, nullptr
	);
	if (hWnd == NULL)
	{
		return 0;
	}

	ShowWindow(hWnd, nShowCmd);


	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}