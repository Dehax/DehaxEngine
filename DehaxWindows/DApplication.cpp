#include "stdafx.h"
#include "DApplication.h"

DApplication::DApplication()
{
}

int DApplication::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (m_hAccelTable != nullptr && !TranslateAcceleratorW(msg.hwnd, m_hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
		else {
			if (m_updateHandler != nullptr) {
				m_updateHandler();
			}
		}
	}

	return (int)msg.wParam;
}

void DApplication::setUpdateHandler(ApplicationUpdateHandler updateHandler)
{
	m_updateHandler = updateHandler;
}
