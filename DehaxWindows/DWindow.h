#pragma once

#include "DehaxWindows.h"

typedef bool(*KeyDownHandler)(unsigned int virtualCode);

class DEHAXWINDOWS_API DWindow {
public:
	DWindow(HINSTANCE hInstance, int x, int y, int width, int height, HICON hIcon, HICON hIconSmall, HCURSOR hCursor, HBRUSH hBackgroundBrush, LPCWSTR lpszMenuName, LPCWSTR lpszClassName, LPCWSTR lpszTitle);
	void Show(int nCmdShow);

	HWND getHandle() const;
	LPCWSTR getTitle() const;

	void setKeyDownHandler(KeyDownHandler keyDownHandler);
private:
	ATOM RegisterWindowClass();
	static LRESULT CALLBACK StaticWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;
	HICON m_hIcon;
	HCURSOR m_hCursor;
	HBRUSH m_hBackgroundBrush;
	LPCWSTR m_lpszMenuName;
	LPCWSTR m_lpszClassName;
	LPCWSTR m_lpszTitle;
	HICON m_hIconSmall;
	HWND m_hWnd;

	KeyDownHandler m_keyDownHandler;
};
