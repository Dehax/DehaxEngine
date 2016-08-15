#include "stdafx.h"
#include "DWindow.h"

DWindow::DWindow(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hBackgroundBrush, LPCWSTR lpszMenuName, LPCWSTR lpszClassName, HICON hIconSmall)
{
	RegisterWindowClass();
}

void DWindow::setUpdateProcedure(DWindowUpdate updateProcedure)
{
	m_updateProcedure = updateProcedure;
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
