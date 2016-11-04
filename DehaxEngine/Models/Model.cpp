#include "..\stdafx.h"
#include "Model.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//Model::Model()
//	: m_mesh(nullptr), m_material(nullptr)
//{
//}

Model::Model(const Model &model)
	: m_material(nullptr)
{
	m_mesh = new Mesh(*model.m_mesh);
	m_material = new Material(*model.m_material);
	m_color = model.m_color;

	m_position = model.m_position;
	m_rotation = model.m_rotation;
	m_scale = model.m_scale;
	m_pivot = model.m_pivot;

	m_transformMatrix = model.m_transformMatrix;
	m_rotateMatrix = model.m_rotateMatrix;
	m_scaleMatrix = model.m_scaleMatrix;
	m_pivotMatrix = model.m_pivotMatrix;
	m_pivotInverseMatrix = model.m_pivotInverseMatrix;

	m_name = model.m_name;
}

Model::Model(LPCWSTR name, Mesh *mesh, const DirectX::XMVECTORF32 &color, Material *material)
	: m_mesh(mesh), m_color(color), m_name(name), m_material(material)
{
	m_position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = DirectX::XMFLOAT3(1.0L, 1.0L, 1.0L);
	m_pivot = DirectX::XMFLOAT3(0.0L, 0.0L, 0.0L);

	m_pivotMatrix = DirectX::XMMatrixIdentity();
	m_pivotInverseMatrix = DirectX::XMMatrixIdentity();
	m_transformMatrix = DirectX::XMMatrixIdentity();
	m_rotateMatrix = DirectX::XMMatrixIdentity();
	m_scaleMatrix = DirectX::XMMatrixIdentity();
}

Model::Model(LPCWSTR filePath, const DirectX::XMVECTORF32 &color, Material *material)
	: Model(L"ModelObj", new Mesh(), color, material)
{
	std::wifstream file(filePath);

	std::vector<DirectX::XMFLOAT3> vertices;
	std::vector<DirectX::XMFLOAT3> verticesNormal;
	std::vector<DirectX::XMUINT3> facesVertexIndex, facesVertexNormalIndex;

	if (file.good()) {
		std::wstring line;
		
		int i = 0;
		while (std::getline(file, line)) {
			std::wistringstream iss(line);
			std::wstring tmp;
			float x, y, z;
			iss >> tmp;

			if (!tmp.compare(L"v")) {
				iss >> x >> y >> z;
				vertices.push_back(DirectX::XMFLOAT3(x, y, z));
			} else if (!tmp.compare(L"vn")) {
				iss >> x >> y >> z;
				verticesNormal.push_back(DirectX::XMFLOAT3(x, y, z));
			} else if (!tmp.compare(L"f")) {
				std::wstring faceText;
				//DirectX::XMUINT3 faceVerticesIndexes, faceNormalsIndexes;

				// ========================
				int vi[3], ni[3];

				for (size_t j = 0; j < 3; j++) {
					iss >> faceText;

					size_t firstDelimiterIndex = faceText.find_first_of(L'/');
					size_t lastDelimiterIndex = faceText.find_last_of(L'/');

					vi[j] = std::wcstol(faceText.substr(0U, firstDelimiterIndex).c_str(), nullptr, 10);
					//int v2 = std::wcstol(first.substr(firstDelimiterIndex, lastDelimiterIndex - firstDelimiterIndex + 1).c_str(), nullptr, 10);
					ni[j] = std::wcstol(faceText.substr(lastDelimiterIndex + 1, faceText.length() - lastDelimiterIndex - 1).c_str(), nullptr, 10);
				}

				facesVertexIndex.push_back(DirectX::XMUINT3(vi[0], vi[1], vi[2]));
				facesVertexNormalIndex.push_back(DirectX::XMUINT3(ni[0], ni[1], ni[2]));

				// =======================

				//iss >> faceText;

				//size_t firstDelimiterIndex = faceText.find_first_of(L'/');
				//size_t lastDelimiterIndex = faceText.find_last_of(L'/');

				//int vertexIndex = std::wcstol(faceText.substr(0U, firstDelimiterIndex).c_str(), nullptr, 10);
				////int v2 = std::wcstol(first.substr(firstDelimiterIndex, lastDelimiterIndex - firstDelimiterIndex + 1).c_str(), nullptr, 10);
				//int normalIndex = std::wcstol(faceText.substr(lastDelimiterIndex + 1, faceText.length() - lastDelimiterIndex - 1).c_str(), nullptr, 10);
				//DirectX::XMFLOAT3 &vn = verticesNormal[normalIndex - 1];
				//DirectX::XMFLOAT3 &v = vertices[vertexIndex - 1];
				//Vertex v1(v.x, v.y, v.z, vn.x, vn.y, vn.z);
				////m_mesh->AddVertex(vertex);

				//iss >> faceText;

				//firstDelimiterIndex = faceText.find_first_of(L'/');
				//lastDelimiterIndex = faceText.find_last_of(L'/');

				//vertexIndex = std::wcstol(faceText.substr(0U, firstDelimiterIndex).c_str(), nullptr, 10);
				////v2 = std::wcstol(first.substr(firstDelimiterIndex, lastDelimiterIndex - firstDelimiterIndex + 1).c_str(), nullptr, 10);
				//normalIndex = std::wcstol(faceText.substr(lastDelimiterIndex + 1, faceText.length() - lastDelimiterIndex - 1).c_str(), nullptr, 10);
				//vn = verticesNormal[normalIndex - 1];
				//v = vertices[vertexIndex - 1];
				//Vertex v2 = Vertex(v.x, v.y, v.z, vn.x, vn.y, vn.z);
				////m_mesh->AddVertex(vertex);

				//iss >> faceText;

				//firstDelimiterIndex = faceText.find_first_of(L'/');
				//lastDelimiterIndex = faceText.find_last_of(L'/');

				//vertexIndex = std::wcstol(faceText.substr(0U, firstDelimiterIndex).c_str(), nullptr, 10);
				////v2 = std::wcstol(first.substr(firstDelimiterIndex, lastDelimiterIndex - firstDelimiterIndex + 1).c_str(), nullptr, 10);
				//normalIndex = std::wcstol(faceText.substr(lastDelimiterIndex + 1, faceText.length() - lastDelimiterIndex - 1).c_str(), nullptr, 10);
				//vn = verticesNormal[normalIndex - 1];
				//v = vertices[vertexIndex - 1];
				//Vertex vertex3 = Vertex(v.x, v.y, v.z, vn.x, vn.y, vn.z);
				////m_mesh->AddVertex(vertex);

				//m_mesh->AddFace(DirectX::XMUINT3(i, i + 1, i + 2));
				i += 3;
			}
		}
	}

	for (size_t i = 0; i < facesVertexIndex.size(); i++) {
		DirectX::XMUINT3 faceVerticesIndexes = facesVertexIndex[i];
		DirectX::XMUINT3 faceNormalsIndexes = facesVertexNormalIndex[i];

		Vertex vertex(vertices[faceVerticesIndexes.x - 1], verticesNormal[faceNormalsIndexes.x - 1]);
		m_mesh->AddVertex(vertex);
		vertex = Vertex(vertices[faceVerticesIndexes.y - 1], verticesNormal[faceNormalsIndexes.y - 1]);
		m_mesh->AddVertex(vertex);
		vertex = Vertex(vertices[faceVerticesIndexes.z - 1], verticesNormal[faceNormalsIndexes.z - 1]);
		m_mesh->AddVertex(vertex);

		m_mesh->AddFace(DirectX::XMUINT3(i * 3, i * 3 + 1, i * 3 + 2));
	}

	//std::vector<DirectX::XMFLOAT3> normalsPerVertex(vertices.size());

	//for (size_t i = 0; i < normalsPerVertex.size(); i++) {
	//	normalsPerVertex[i] = DirectX::XMFLOAT3(face);
	//}

	//for (size_t i = 0; i < vertices.size(); i++) {
	//	Vertex vertex(vertices[i].x, vertices[i].y, vertices[i].z, normalsPerVertex[i].x, normalsPerVertex[i].y, normalsPerVertex[i].z);
	//	m_mesh->AddVertex(vertex);
	//}

	file.close();
}

Model::~Model()
{
	if (m_mesh != nullptr) {
		delete m_mesh;
		m_mesh = nullptr;
	}

	if (m_material != nullptr) {
		delete m_material;
		m_material = nullptr;
	}
}

DirectX::XMFLOAT3 Model::getPosition() const
{
	return m_position;
}

void Model::setPosition(DirectX::XMFLOAT3 position)
{
	m_position = position;

	m_transformMatrix = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
}

DirectX::XMFLOAT3 Model::getRotation() const
{
	return m_rotation;
}

void Model::setRotation(DirectX::XMFLOAT3 rotation)
{
	m_rotation = rotation;

	m_rotateMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
}

DirectX::XMFLOAT3 Model::getScale() const
{
	return m_scale;
}

void Model::setScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;

	m_scaleMatrix = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
}

DirectX::XMFLOAT3 Model::getPivot() const
{
	return m_pivot;
}

void Model::setPivot(DirectX::XMFLOAT3 pivot)
{
	m_pivot = pivot;
}

Mesh *Model::getMesh()
{
	return m_mesh;
}

DirectX::XMMATRIX Model::getWorldMatrix()
{
	DirectX::XMMATRIX P = m_pivotMatrix;
	DirectX::XMMATRIX R = m_rotateMatrix;
	DirectX::XMMATRIX S = m_scaleMatrix;
	DirectX::XMMATRIX PI = m_pivotInverseMatrix;
	DirectX::XMMATRIX T = m_transformMatrix;

	return P * R * S * PI * T;
}

LPCWSTR Model::getName() const
{
	return m_name;
}

void Model::setName(LPCWSTR name)
{
	m_name = name;
}

DirectX::XMVECTORF32 Model::getColor() const
{
	return m_color;
}

void Model::setColor(const DirectX::XMVECTORF32 &color)
{
	m_color = color;
}

Material *Model::getMaterial() const
{
	return m_material;
}

void Model::setMaterial(Material *material)
{
	if (m_material != nullptr) {
		delete m_material;
	}

	m_material = material;
}

Model &Model::operator=(const Model &model)
{
	if (this != &model) {
		if (m_mesh != nullptr) {
			delete m_mesh;
		}

		m_mesh = new Mesh(*model.m_mesh);
		m_color = model.m_color;

		m_position = model.m_position;
		m_rotation = model.m_rotation;
		m_scale = model.m_scale;
		m_pivot = model.m_pivot;

		m_transformMatrix = model.m_transformMatrix;
		m_rotateMatrix = model.m_rotateMatrix;
		m_scaleMatrix = model.m_scaleMatrix;
		m_pivotMatrix = model.m_pivotMatrix;
		m_pivotInverseMatrix = model.m_pivotInverseMatrix;

		m_name = model.m_name;
	}

	return *this;
}
