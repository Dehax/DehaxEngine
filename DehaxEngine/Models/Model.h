#pragma once
#include "..\stdafx.h"

#include <string>

#include "Mesh.h"

class DEHAXENGINE_API Model {
public:
	explicit Model();
	explicit Model(const Model &model);
	explicit Model(const char *name, Mesh *mesh, const DirectX::XMVECTORF32 &color);
	~Model();

	DirectX::XMFLOAT3 getPosition() const;
	void setPosition(DirectX::XMFLOAT3 position);
	DirectX::XMFLOAT3 getRotation() const;
	void setRotation(DirectX::XMFLOAT3 rotation);
	DirectX::XMFLOAT3 getScale() const;
	void setScale(DirectX::XMFLOAT3 scale);
	DirectX::XMFLOAT3 getPivot() const;
	void setPivot(DirectX::XMFLOAT3 pivot);
	Mesh *getMesh();

	DirectX::XMMATRIX worldMatrix();

	const char *getName() const;
	void setName(const char *name);
	DirectX::XMVECTORF32 getColor() const;
	void setColor(const DirectX::XMVECTORF32 &color);

	Model &operator=(const Model &model);
private:
	Mesh *m_mesh;
	DirectX::XMVECTORF32 m_color;

	// World
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_scale;
	DirectX::XMFLOAT3 m_pivot;

	DirectX::XMMATRIX m_transformMatrix;
	DirectX::XMMATRIX m_rotateMatrix;
	DirectX::XMMATRIX m_scaleMatrix;
	DirectX::XMMATRIX m_pivotMatrix;
	DirectX::XMMATRIX m_pivotInverseMatrix;

	const char *m_name;
};
