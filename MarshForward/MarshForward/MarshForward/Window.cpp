#include "Window.h"
#include <iostream>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
	: n_hInstance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"My Window Class";
	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = n_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc; // fix later

	RegisterClass(&wndClass);
	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT rect;
	int width{ 1920 };
	int height{ 1080 };

	rect.left = 250;
	rect.right = rect.left + width;
	rect.top = 250;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	n_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Marsh Forward" + FPScounter(),
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		n_hInstance,
		NULL
	);

	ShowWindow(n_hWnd, SW_SHOW);
}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"My Window Class";
	UnregisterClass(CLASS_NAME, n_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

void Window::FPScounter()
{
	clock_t c_ticks, d_ticks;
	clock_t fps{ 0 };
	d_ticks = clock() - c_ticks;
	if (d_ticks > 0) {
		fps = CLOCKS_PER_SEC / d_ticks;
	}
	std::cout << fps;
	
}

