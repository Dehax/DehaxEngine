#include "stdafx.h"
#include "DWindow.h"

DWindow::DWindow(HINSTANCE hInstance, int x, int y, int width, int height, HICON hIcon, HICON hIconSmall, HCURSOR hCursor, HBRUSH hBackgroundBrush, LPCWSTR lpszMenuName, LPCWSTR lpszClassName, LPCWSTR lpszTitle)
	: m_hInstance(hInstance), m_hIcon(hIcon), m_hIconSmall(hIconSmall), m_hCursor(hCursor), m_hBackgroundBrush(hBackgroundBrush), m_lpszMenuName(lpszMenuName), m_lpszClassName(lpszClassName), m_lpszTitle(lpszTitle)
{
	RegisterWindowClass();

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, m_lpszMenuName != nullptr);

	m_hWnd = CreateWindowExW(0L, m_lpszClassName, m_lpszTitle, WS_OVERLAPPEDWINDOW,
		x, y, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, this);
}

void DWindow::Show(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);
}

HWND DWindow::getHandle() const
{
	return m_hWnd;
}

LPCWSTR DWindow::getTitle() const
{
	return m_lpszTitle;
}

void DWindow::setKeyDownHandler(KeyDownHandler keyDownHandler)
{
	m_keyDownHandler = keyDownHandler;
}

ATOM DWindow::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = StaticWindowProcedure;
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

LRESULT DWindow::StaticWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LONG dwNewLong;
	DWindow *pWin;

	if (message == WM_NCCREATE)
	{
		dwNewLong = (long)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		SetWindowLongW(hWnd, GWL_USERDATA, dwNewLong);
		return TRUE;
	}
	else
	{
		pWin = (DWindow *)GetWindowLongW(hWnd, GWL_USERDATA);
	}

	if (pWin) {
		return pWin->WindowProcedure(hWnd, message, wParam, lParam);
	}

	return 0;
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
	case WM_KEYDOWN:
	{
		if (m_keyDownHandler != nullptr) {
			m_keyDownHandler(wParam);
		}
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
