#include "..\stdafx.h"
#include "ModelsFactory.h"

Model ModelsFactory::Box(float width, float length, float height)
{
	width /= 2.0f;
	length /= 2.0f;
	height /= 2.0f;

	Mesh *mesh = new Mesh();
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	Material *material = new Material(L"SimpleColor_VS.cso", L"SimpleColor_PS.cso", layout, numElements);
	Model model(L"(G) box", mesh, DirectX::Colors::Red, material);

	// +Y
	mesh->AddVertex(Vertex(-length, height, -width, 0.0f, 1.0f, 0.0f));		// 0
	mesh->AddVertex(Vertex(length, height, -width, 0.0f, 1.0f, 0.0f));		// 1
	mesh->AddVertex(Vertex(length, height, width, 0.0f, 1.0f, 0.0f));		// 2
	mesh->AddVertex(Vertex(-length, height, width, 0.0f, 1.0f, 0.0f));		// 3
	// -Y
	mesh->AddVertex(Vertex(-length, -height, -width, 0.0f, -1.0f, 0.0f));	// 4
	mesh->AddVertex(Vertex(length, -height, -width, 0.0f, -1.0f, 0.0f));	// 5
	mesh->AddVertex(Vertex(length, -height, width, 0.0f, -1.0f, 0.0f));		// 6
	mesh->AddVertex(Vertex(-length, -height, width, 0.0f, -1.0f, 0.0f));	// 7
	// -X
	mesh->AddVertex(Vertex(-length, -height, width, -1.0f, 0.0f, 0.0f));	// 0
	mesh->AddVertex(Vertex(-length, -height, -width, -1.0f, 0.0f, 0.0f));	// 1
	mesh->AddVertex(Vertex(-length, height, -width, -1.0f, 0.0f, 0.0f));	// 2
	mesh->AddVertex(Vertex(-length, height, width, -1.0f, 0.0f, 0.0f));		// 3
	// +X
	mesh->AddVertex(Vertex(length, -height, width, 1.0f, 0.0f, 0.0f));		// 0
	mesh->AddVertex(Vertex(length, -height, -width, 1.0f, 0.0f, 0.0f));		// 1
	mesh->AddVertex(Vertex(length, height, -width, 1.0f, 0.0f, 0.0f));		// 2
	mesh->AddVertex(Vertex(length, height, width, 1.0f, 0.0f, 0.0f));		// 3
	// -Z
	mesh->AddVertex(Vertex(-length, -height, -width, 0.0f, 0.0f, -1.0f));	// 0
	mesh->AddVertex(Vertex(length, -height, -width, 0.0f, 0.0f, -1.0f));	// 1
	mesh->AddVertex(Vertex(length, height, -width, 0.0f, 0.0f, -1.0f));		// 2
	mesh->AddVertex(Vertex(-length, height, -width, 0.0f, 0.0f, -1.0f));	// 3
	// +Z
	mesh->AddVertex(Vertex(-length, -height, width, 0.0f, 0.0f, 1.0f));		// 0
	mesh->AddVertex(Vertex(length, -height, width, 0.0f, 0.0f, 1.0f));		// 1
	mesh->AddVertex(Vertex(length, height, width, 0.0f, 0.0f, 1.0f));		// 2
	mesh->AddVertex(Vertex(-length, height, width, 0.0f, 0.0f, 1.0f));		// 3

	mesh->AddFace(DirectX::XMUINT3(3, 1, 0));
	mesh->AddFace(DirectX::XMUINT3(2, 1, 3));
	mesh->AddFace(DirectX::XMUINT3(6, 4, 5));
	mesh->AddFace(DirectX::XMUINT3(7, 4, 6));
	mesh->AddFace(DirectX::XMUINT3(11, 9, 8));
	mesh->AddFace(DirectX::XMUINT3(10, 9, 11));
	mesh->AddFace(DirectX::XMUINT3(14, 12, 13));
	mesh->AddFace(DirectX::XMUINT3(15, 12, 14));
	mesh->AddFace(DirectX::XMUINT3(19, 17, 16));
	mesh->AddFace(DirectX::XMUINT3(18, 17, 19));
	mesh->AddFace(DirectX::XMUINT3(22, 20, 21));
	mesh->AddFace(DirectX::XMUINT3(23, 20, 22));

	return model;
}

//Model ModelsFactory::Cylinder(float radius, float height, int sides)
//{
//	height /= 2.0f;
//
//	Mesh *mesh = new Mesh();
//	Model model(L"(G) cylinder", mesh, DirectX::Colors::Blue);
//
//	int nbVerticesCap = sides + 1;
//
//	int verticesLength = nbVerticesCap + nbVerticesCap;// + sides * 2 + 2;
//
//	Vertex *vertices = new Vertex[verticesLength];
//	int vert = 0;
//
//	// Bottom cap
//	// Центральная вершина нижней крышки
//	vertices[vert++] = Vertex(0.0f, -height, 0.0f);
//
//	while (vert <= sides) {
//		float rad = (float)vert / sides * DirectX::XM_2PI;
//		vertices[vert] = Vertex(std::cos(rad) * radius, -height, std::sin(rad) * radius);
//		vert++;
//	}
//
//	// Top cap
//	vertices[vert++] = Vertex(0.0L, height, 0.0L);
//
//	while (vert <= sides * 2 + 1) {
//		float rad = (float)(vert - sides - 1) / sides * DirectX::XM_2PI;
//		vertices[vert] = Vertex(std::cos(rad) * radius, height, std::sin(rad) * radius);
//		vert++;
//	}
//
//	// Triangles
//	int nbTriangles = sides * 4;//sides * sides;// + sides * 2;
//	int *triangles = new int[nbTriangles * 3/* + 3*/];
//
//	// Bottom cap
//	int tri = 0;
//	int i = 0;
//
//	while (tri < sides - 1) {
//		triangles[i] = 0;
//		triangles[i + 1] = tri + 1;
//		triangles[i + 2] = tri + 2;
//		tri++;
//		i += 3;
//	}
//
//	triangles[i] = 0;
//	triangles[i + 1] = tri + 1;
//	triangles[i + 2] = 1;
//	tri++;
//	i += 3;
//
//	// Top cap
//	tri++;
//
//	while (tri < sides * 2) {
//		triangles[i] = tri + 2;
//		triangles[i + 1] = tri + 1;
//		triangles[i + 2] = nbVerticesCap;
//		tri++;
//		i += 3;
//	}
//
//	triangles[i] = nbVerticesCap + 1;
//	triangles[i + 1] = tri + 1;
//	triangles[i + 2] = nbVerticesCap;
//	tri++;
//	i += 3;
//	tri++;
//
//	// Sides
//	int j = tri;
//
//	while (j <= nbTriangles - 2) {
//		triangles[i] = tri - nbVerticesCap * 2 + 1;
//		triangles[i + 1] = tri - nbVerticesCap + 1;
//		triangles[i + 2] = tri - nbVerticesCap * 2 + 2;
//		//tri++;
//		j++;
//		i += 3;
//
//		triangles[i] = tri - nbVerticesCap * 2 + 2;
//		triangles[i + 1] = tri - nbVerticesCap + 1;
//		triangles[i + 2] = tri - nbVerticesCap + 2;
//		tri++;
//		j++;
//		i += 3;
//	}
//
//	triangles[i] = tri - nbVerticesCap * 2 + 1;
//	triangles[i + 1] = tri - nbVerticesCap + 1;
//	triangles[i + 2] = 1;
//	i += 3;
//
//	triangles[i] = 1;
//	triangles[i + 1] = tri - nbVerticesCap + 1;
//	triangles[i + 2] = 1 + nbVerticesCap;
//
//	for (int i = 0; i < verticesLength; i++) {
//		mesh->AddVertex(vertices[i]);
//	}
//
//	for (int i = 0; i < nbTriangles * 3; i += 3) {
//		mesh->AddFace(DirectX::XMUINT3(triangles[i], triangles[i + 1], triangles[i + 2]));
//	}
//
//	delete[] triangles;
//	delete[] vertices;
//
//	return model;
//}
