#include "stdafx.h"
#include "DehaxGame.h"

#include <Models\Mesh.h>
#include <Models\ModelsFactory.h>

//#define FIND_MEMORY_LEAKS

#ifdef FIND_MEMORY_LEAKS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#endif  // FIND_MEMORY_LEAKS

const float MOUSE_CAMERA_MOVE_SCALE = 0.1f;

DehaxEngine *g_dehaxEngine;
Model *g_objMonkeyModel;

HWND g_hWnd;

bool g_isMousePressed = false;
POINT g_lastMousePosition;

// Определить разметку входных данных вершинного шейдера
D3D11_INPUT_ELEMENT_DESC g_layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};
UINT g_numElements = ARRAYSIZE(g_layout);

void Update()
{
	g_dehaxEngine->getRenderer()->Render();
}

bool KeyDown(unsigned int virtualCode)
{
	switch (virtualCode)
	{
	case 0x57: // W
	{
		g_dehaxEngine->getRenderer()->getCamera()->StrafeForward(1.0f);

		return true;
	}
	break;
	case 0x53: // S
	{
		g_dehaxEngine->getRenderer()->getCamera()->StrafeForward(-1.0f);
	}
	break;
	case 0x41: // A
	{
		g_dehaxEngine->getRenderer()->getCamera()->StrafeRight(-1.0f);

		return true;
	}
	break;
	case 0x44: // D
	{
		g_dehaxEngine->getRenderer()->getCamera()->StrafeRight(1.0f);
	}
	break;
	case 0x51: // Q
	{
		g_dehaxEngine->getRenderer()->getCamera()->StrafeUp(-1.0f);
	}
	break;
	case 0x45: // E
	{
		g_dehaxEngine->getRenderer()->getCamera()->StrafeUp(1.0f);
	}
	break;
	case VK_RIGHT:
	{
		DirectX::XMFLOAT3 position = g_objMonkeyModel->getPosition();
		g_objMonkeyModel->setPosition(DirectX::XMFLOAT3(position.x + 0.5f, position.y, position.z));
		
		return true;
	}
	break;
	case VK_LEFT:
	{
		DirectX::XMFLOAT3 position = g_objMonkeyModel->getPosition();
		g_objMonkeyModel->setPosition(DirectX::XMFLOAT3(position.x - 0.5f, position.y, position.z));
		return true;
	}
	break;
	case VK_UP:
	{
		DirectX::XMFLOAT3 position = g_objMonkeyModel->getPosition();
		g_objMonkeyModel->setPosition(DirectX::XMFLOAT3(position.x, position.y + 0.5f, position.z));

		return true;
	}
	break;
	case VK_DOWN:
	{
		DirectX::XMFLOAT3 position = g_objMonkeyModel->getPosition();
		g_objMonkeyModel->setPosition(DirectX::XMFLOAT3(position.x, position.y - 0.5f, position.z));

		return true;
	}
	break;
	case VK_NUMPAD6:
	{
		g_dehaxEngine->getRenderer()->getCamera()->Rotate(0.0f, DirectX::XMConvertToRadians(1.0f), 0.0f);

		return true;
	}
	break;
	case VK_NUMPAD4:
	{
		g_dehaxEngine->getRenderer()->getCamera()->Rotate(0.0f, -DirectX::XMConvertToRadians(1.0f), 0.0f);

		return true;
	}
	break;
	case VK_NUMPAD8:
	{
		g_dehaxEngine->getRenderer()->getCamera()->Rotate(DirectX::XMConvertToRadians(1.0f), 0.0f, 0.0f);

		return true;
	}
	break;
	case VK_NUMPAD2:
	{
		g_dehaxEngine->getRenderer()->getCamera()->Rotate(-DirectX::XMConvertToRadians(1.0f), 0.0f, 0.0f);

		return true;
	}
	break;
	case VK_ADD:
	case VK_OEM_PLUS:
	{
		g_dehaxEngine->getRenderer()->getCamera()->Zoom(2.0f);

		return true;
	}
	break;
	case VK_SUBTRACT:
	case VK_OEM_MINUS:
	{
		g_dehaxEngine->getRenderer()->getCamera()->Zoom(-2.0f);

		return true;
	}
	break;
	case VK_F2:
	{
		Material *material = new Material(L"SimpleColor_VS.cso", L"SimpleColor_PS.cso", g_layout, g_numElements);
		g_objMonkeyModel = new Model(ModelsFactory::Box());
		g_dehaxEngine->getScene()->AddModel(g_objMonkeyModel);
	}
	break;
	case 0x50: // P
	{
		g_dehaxEngine->getRenderer()->getCamera()->ChangeProjection();

		return true;
	}
	break;
	case 0x4F: // O
	{
		OPENFILENAME ofn = { 0 };
		wchar_t szFile[MAX_PATH];

		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = L'\0';
		ofn.hwndOwner = g_hWnd;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = L"Wavefront OBJ(*.obj)\0*.obj\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrInitialDir = nullptr;
		ofn.lpstrFileTitle = nullptr;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		Material *material = new Material(L"SimpleColor_VS.cso", L"SimpleColor_PS.cso", g_layout, g_numElements);

		wchar_t currentDirectoryPath[MAX_PATH];
		GetCurrentDirectoryW(MAX_PATH, currentDirectoryPath);

		BOOL isOpened = GetOpenFileNameW(&ofn);

		SetCurrentDirectoryW(currentDirectoryPath);

		if (isOpened) {
			g_objMonkeyModel = new Model(ofn.lpstrFile, DirectX::Colors::Red, material);

			g_dehaxEngine->getScene()->AddModel(g_objMonkeyModel);

			return true;
		}
	}
	break;
	}

	return false;
}

LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (wParam == MK_LBUTTON) {
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			g_isMousePressed = true;
			g_lastMousePosition = { x, y };
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (!g_isMousePressed) {
			break;
		}

		if (wParam == MK_LBUTTON) {
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			POINT mousePosition = { x, y };

			int deltaX = mousePosition.x - g_lastMousePosition.x;
			int deltaY = mousePosition.y - g_lastMousePosition.y;

			if (deltaX == 0 && deltaY == 0) {
				break;
			}

			g_dehaxEngine->getRenderer()->getCamera()->Rotate(DirectX::XMConvertToRadians(-deltaY * MOUSE_CAMERA_MOVE_SCALE), DirectX::XMConvertToRadians(-deltaX * MOUSE_CAMERA_MOVE_SCALE), 0.0f);

			g_lastMousePosition = mousePosition;
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (wParam == MK_LBUTTON) {
			g_isMousePressed = false;
		}
	}
	break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef FIND_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif  // FIND_MEMORY_LEAKS

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
		/*MAKEINTRESOURCEW(IDC_DEHAXGAME)*/nullptr,
		szWindowClass,
		szTitle);
	window.setKeyDownHandler(KeyDown);
	window.setWindowMessageHandler(WindowProcedure);
	window.Show(nCmdShow);
	g_hWnd = window.getHandle();

	application.setUpdateHandler(Update);

	Material *monkeyMaterial = new Material(L"SimpleColor_VS.cso", L"SimpleColor_PS.cso", g_layout, g_numElements);
	g_objMonkeyModel = new Model(L"..\\monkey.obj", DirectX::Colors::Red, monkeyMaterial);

	g_dehaxEngine = new DehaxEngine();
	g_dehaxEngine->getScene()->AddModel(g_objMonkeyModel);
	g_dehaxEngine->getRenderer()->InitDevice(window.getHandle());

	int resultCode = application.Run();

	delete g_dehaxEngine;

	return resultCode;
}
