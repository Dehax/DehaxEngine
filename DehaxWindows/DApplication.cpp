#include "stdafx.h"
#include "DApplication.h"

DApplication::DApplication()
{
}

int DApplication::Run()
{
	MSG msg;

	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		if (m_hAccelTable != nullptr && !TranslateAcceleratorW(msg.hwnd, m_hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	return (int)msg.wParam;
}
