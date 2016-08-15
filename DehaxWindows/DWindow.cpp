#include "stdafx.h"
#include "DWindow.h"

DWindow::DWindow(HINSTANCE hInstance, HICON hIcon, HICON hIconSmall, HCURSOR hCursor, HBRUSH hBackgroundBrush, LPCWSTR lpszMenuName, LPCWSTR lpszClassName, LPCWSTR lpszTitle)
	: m_hInstance(hInstance), m_hIcon(hIcon), m_hIconSmall(hIconSmall), m_hCursor(hCursor), m_hBackgroundBrush(hBackgroundBrush), m_lpszMenuName(lpszMenuName), m_lpszClassName(lpszClassName), m_lpszTitle(lpszTitle)
{
	RegisterWindowClass();

	m_hWnd = CreateWindowExW(0L, m_lpszClassName, m_lpszTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);
}

void DWindow::Show(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);
}

ATOM DWindow::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProcedure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = m_hIcon;
	wcex.hCursor = m_hCursor;
	wcex.hbrBackground = m_hBackgroundBrush;
	wcex.lpszMenuName = m_lpszMenuName;
	wcex.lpszClassName = m_lpszClassName;
	wcex.hIconSm = m_hIconSmall;

	return RegisterClassExW(&wcex);
}

LRESULT DWindow::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}

	return 0;
}
