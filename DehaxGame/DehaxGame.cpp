#include "stdafx.h"
#include "DehaxGame.h"

#include <Models\Mesh.h>
#include <Models\ModelsFactory.h>

const float MOUSE_CAMERA_MOVE_SCALE = 0.1f;

DehaxEngine *g_dehaxEngine;
//Model *g_smallBox;
//Model *g_bigBox;
Model *g_objBoxModel;

bool g_isMousePressed = false;
POINT g_lastMousePosition;

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
	case VK_RIGHT:
	{
		DirectX::XMFLOAT3 position = g_objBoxModel->getPosition();
		g_objBoxModel->setPosition(DirectX::XMFLOAT3(position.x + 0.5f, position.y, position.z));
		
		return true;
	}
	break;
	case VK_LEFT:
	{
		DirectX::XMFLOAT3 position = g_objBoxModel->getPosition();
		g_objBoxModel->setPosition(DirectX::XMFLOAT3(position.x - 0.5f, position.y, position.z));

		return true;
	}
	break;
	case VK_UP:
	{
		DirectX::XMFLOAT3 position = g_objBoxModel->getPosition();
		g_objBoxModel->setPosition(DirectX::XMFLOAT3(position.x, position.y + 0.5f, position.z));

		return true;
	}
	break;
	case VK_DOWN:
	{
		DirectX::XMFLOAT3 position = g_objBoxModel->getPosition();
		g_objBoxModel->setPosition(DirectX::XMFLOAT3(position.x, position.y - 0.5f, position.z));

		return true;
	}
	break;
	case 0x4C: // L
	{
		//DirectX::XMFLOAT3 position = g_bigBox->getPosition();
		//g_bigBox->setPosition(DirectX::XMFLOAT3(position.x + 0.5f, position.y, position.z));

		return true;
	}
	break;
	case 0x4A: // J
	{
		//DirectX::XMFLOAT3 position = g_bigBox->getPosition();
		//g_bigBox->setPosition(DirectX::XMFLOAT3(position.x - 0.5f, position.y, position.z));

		return true;
	}
	break;
	case 0x49: // I
	{
		//DirectX::XMFLOAT3 position = g_bigBox->getPosition();
		//g_bigBox->setPosition(DirectX::XMFLOAT3(position.x, position.y + 0.5f, position.z));

		return true;
	}
	break;
	case 0x4B: // K
	{
		//DirectX::XMFLOAT3 position = g_bigBox->getPosition();
		//g_bigBox->setPosition(DirectX::XMFLOAT3(position.x, position.y - 0.5f, position.z));

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
	case 0x50:
	{
		g_dehaxEngine->getRenderer()->getCamera()->ChangeProjection();

		return true;
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
	window.setKeyDownHandler(KeyDown);
	window.setWindowMessageHandler(WindowProcedure);
	window.Show(nCmdShow);

	application.setUpdateHandler(Update);

	//g_smallBox = new Model(ModelsFactory::Box());
	//g_bigBox = new Model(ModelsFactory::Box(2.0f, 4.0f, 8.0f));
	//g_bigBox->setColor(DirectX::Colors::Yellow);

	// Определить разметку входных данных вершинного шейдера
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	Material *material = new Material(L"SimpleColor_VS.cso", L"SimpleColor_PS.cso", layout, numElements);
	g_objBoxModel = new Model(L"..\\cube.obj", DirectX::Colors::GreenYellow, material);

	g_dehaxEngine = new DehaxEngine();
	//g_dehaxEngine->getScene()->AddModel(g_smallBox);
	//g_dehaxEngine->getScene()->AddModel(g_bigBox);
	g_dehaxEngine->getScene()->AddModel(g_objBoxModel);
	g_dehaxEngine->getRenderer()->InitDevice(window.getHandle());

	int resultCode = application.Run();

	delete g_dehaxEngine;

	return resultCode;
}
