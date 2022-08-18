#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window(); 
	~Window();

	bool ProcessMessages();
	void FPScounter();
private:
	HINSTANCE n_hInstance;
	HWND n_hWnd;

};

