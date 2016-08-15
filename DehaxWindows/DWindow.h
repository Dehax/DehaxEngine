#pragma once

#include "DehaxWindows.h"

class DEHAXWINDOWS_API DWindow {
public:
	DWindow(HINSTANCE hInstance, HICON hIcon, HICON hIconSmall, HCURSOR hCursor, HBRUSH hBackgroundBrush, LPCWSTR lpszMenuName, LPCWSTR lpszClassName, LPCWSTR lpszTitle);
	void Show(int nCmdShow);
private:
	ATOM RegisterWindowClass();
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;
	HICON m_hIcon;
	HCURSOR m_hCursor;
	HBRUSH m_hBackgroundBrush;
	LPCWSTR m_lpszMenuName;
	LPCWSTR m_lpszClassName;
	LPCWSTR m_lpszTitle;
	HICON m_hIconSmall;
	HWND m_hWnd;
};
