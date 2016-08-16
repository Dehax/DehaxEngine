#include "stdafx.h"
#include "DehaxGame.h"

DehaxEngine *dehaxEngine;

void Update()
{
	dehaxEngine->Render();
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WCHAR szTitle[100];
	WCHAR szWindowClass[100];
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, 100);
	LoadStringW(hInstance, IDC_DEHAXGAME, szWindowClass, 100);

	HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCEW(IDC_DEHAXGAME));

	DApplication application;
	DWindow window = DWindow(hInstance, 0, 0, 800, 600,
		LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_DEHAXGAME)),
		LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_SMALL)),
		LoadCursorW(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCEW(IDC_DEHAXGAME),
		szWindowClass,
		szTitle);
	window.Show(nCmdShow);

	application.setUpdateHandler(Update);

	dehaxEngine = new DehaxEngine(window.getHandle());

	int resultCode = application.Run();

	delete dehaxEngine;

	return resultCode;
}
