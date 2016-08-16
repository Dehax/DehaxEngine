#include "stdafx.h"
#include "DehaxGame.h"

#include <Models\Mesh.h>

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

	Mesh *mesh = new Mesh();
	mesh->AddVertex(Vertex(-1.0f, 1.0f, -1.0f));
	mesh->AddVertex(Vertex(1.0f, 1.0f, -1.0f));
	mesh->AddVertex(Vertex(1.0f, 1.0f, 1.0f));
	mesh->AddVertex(Vertex(-1.0f, 1.0f, 1.0f));
	mesh->AddVertex(Vertex(-1.0f, -1.0f, -1.0f));
	mesh->AddVertex(Vertex(1.0f, -1.0f, -1.0f));
	mesh->AddVertex(Vertex(1.0f, -1.0f, 1.0f));
	mesh->AddVertex(Vertex(-1.0f, -1.0f, 1.0f));
	mesh->AddFace(DirectX::XMUINT3(3, 1, 0));
	mesh->AddFace(DirectX::XMUINT3(2, 1, 3));
	mesh->AddFace(DirectX::XMUINT3(0, 5, 4));
	mesh->AddFace(DirectX::XMUINT3(1, 5, 0));
	mesh->AddFace(DirectX::XMUINT3(3, 4, 7));
	mesh->AddFace(DirectX::XMUINT3(0, 4, 3));
	mesh->AddFace(DirectX::XMUINT3(1, 6, 5));
	mesh->AddFace(DirectX::XMUINT3(2, 6, 1));
	mesh->AddFace(DirectX::XMUINT3(2, 7, 6));
	mesh->AddFace(DirectX::XMUINT3(3, 7, 2));
	mesh->AddFace(DirectX::XMUINT3(6, 4, 5));
	mesh->AddFace(DirectX::XMUINT3(7, 4, 6));
	Model *model = new Model("DehaxModel", mesh, DirectX::Colors::Black);

	dehaxEngine->setModel(model);
	dehaxEngine->InitDevice();

	int resultCode = application.Run();

	delete dehaxEngine;

	return resultCode;
}
