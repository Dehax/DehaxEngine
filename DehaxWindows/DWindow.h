#pragma once

#include "DehaxWindows.h"

typedef bool(*KeyDownHandler)(unsigned int virtualCode);
typedef LRESULT(*WindowMessageHandler)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class DEHAXWINDOWS_API DWindow {
public:
	DWindow(HINSTANCE hInstance, int x, int y, int width, int height, HICON hIcon, HICON hIconSmall, HCURSOR hCursor, HBRUSH hBackgroundBrush, LPCWSTR lpszMenuName, LPCWSTR lpszClassName, LPCWSTR lpszTitle);
	void Show(int nCmdShow);

	HWND getHandle() const;
	LPCWSTR getTitle() const;

	void setKeyDownHandler(KeyDownHandler keyDownHandler);
	void setWindowMessageHandler(WindowMessageHandler windowMessageHandler);
private:
	ATOM RegisterWindowClass();
	static LRESULT CALLBACK StaticWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance = nullptr;
	HICON m_hIcon = nullptr;
	HCURSOR m_hCursor = nullptr;
	HBRUSH m_hBackgroundBrush = nullptr;
	LPCWSTR m_lpszMenuName = nullptr;
	LPCWSTR m_lpszClassName = nullptr;
	LPCWSTR m_lpszTitle = nullptr;
	HICON m_hIconSmall = nullptr;
	HWND m_hWnd = nullptr;

	KeyDownHandler m_keyDownHandler = nullptr;
	WindowMessageHandler m_windowMessageHandler = nullptr;
};
