#include "stdafx.h"
#include "DehaxGame.h"

#include <Models\Mesh.h>
#include <Models\ModelsFactory.h>

DehaxEngine *dehaxEngine;
Model *model;

void Update()
{
	dehaxEngine->getRenderer()->Render();
}

bool KeyDown(unsigned int virtualCode)
{
	switch (virtualCode)
	{
	case VK_RIGHT:
	{
		DirectX::XMFLOAT3 position = model->getPosition();
		model->setPosition(DirectX::XMFLOAT3(position.x + 0.5f, position.y, position.z));
		
		return true;
	}
	break;
	case VK_LEFT:
	{
		DirectX::XMFLOAT3 position = model->getPosition();
		model->setPosition(DirectX::XMFLOAT3(position.x - 0.5f, position.y, position.z));

		return true;
	}
	break;
	default:
	case VK_UP:
	{
		DirectX::XMFLOAT3 position = model->getPosition();
		model->setPosition(DirectX::XMFLOAT3(position.x, position.y + 0.5f, position.z));

		return true;
	}
	break;
	case VK_DOWN:
	{
		DirectX::XMFLOAT3 position = model->getPosition();
		model->setPosition(DirectX::XMFLOAT3(position.x, position.y - 0.5f, position.z));

		return true;
	}
	break;
		break;
	}

	return false;
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
	window.Show(nCmdShow);

	application.setUpdateHandler(Update);

	model = new Model(ModelsFactory::Box());

	dehaxEngine = new DehaxEngine();
	dehaxEngine->getScene()->AddModel(model);
	dehaxEngine->getRenderer()->InitDevice(window.getHandle());

	int resultCode = application.Run();

	delete dehaxEngine;

	return resultCode;
}
