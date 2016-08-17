#pragma once
#include "..\stdafx.h"

struct DEHAXENGINE_API Vertex {
public:
	Vertex();
	Vertex(const float &x, const float &y, const float &z, const float &normalX, const float &normalY, const float &normalZ);
	Vertex(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &normal);

	float getX() const;
	float getY() const;
	float getZ() const;
	DirectX::XMFLOAT3 getPosition() const;
	DirectX::XMFLOAT3 getNormal() const;
private:
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_normal;
};
