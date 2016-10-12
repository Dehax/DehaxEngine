#pragma once
#include "..\stdafx.h"

#include <string>

#include "Mesh.h"
#include "Material.h"

class DEHAXENGINE_API Model {
public:
	//Model();
	Model(const Model &model);
	Model(LPCWSTR name, Mesh *mesh, const DirectX::XMVECTORF32 &color, Material *material);
	Model(LPCWSTR filePath, const DirectX::XMVECTORF32 &color, Material *material);
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

	DirectX::XMMATRIX getWorldMatrix();

	LPCWSTR getName() const;
	void setName(LPCWSTR name);
	DirectX::XMVECTORF32 getColor() const;
	void setColor(const DirectX::XMVECTORF32 &color);

	Material *getMaterial() const;
	void setMaterial(Material *material);

	Model &operator=(const Model &model);
private:
	Mesh *m_mesh = nullptr;
	DirectX::XMVECTORF32 m_color;

	Material *m_material;

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

	LPCWSTR m_name = nullptr;
};
