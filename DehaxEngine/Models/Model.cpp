#include "..\stdafx.h"
#include "Model.h"

Model::Model()
	: m_mesh(nullptr)
{
}

Model::Model(const Model &model)
{
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

Model::Model(const char *name, Mesh *mesh, const DirectX::XMVECTORF32 &color)
	: m_mesh(mesh), m_color(color), m_name(name)
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

Model::~Model()
{
	if (m_mesh != nullptr) {
		delete m_mesh;
		m_mesh = nullptr;
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

DirectX::XMMATRIX Model::worldMatrix()
{
	DirectX::XMMATRIX P = m_pivotMatrix;
	DirectX::XMMATRIX R = m_rotateMatrix;
	DirectX::XMMATRIX S = m_scaleMatrix;
	DirectX::XMMATRIX PI = m_pivotInverseMatrix;
	DirectX::XMMATRIX T = m_transformMatrix;

	return P * R * S * PI * T;
}

const char *Model::getName() const
{
	return m_name;
}

void Model::setName(const char *name)
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
