#pragma once
#include "..\stdafx.h"

struct DEHAXENGINE_API Vertex {
public:
	explicit Vertex();
	explicit Vertex(const float &x, const float &y, const float &z);
	explicit Vertex(const DirectX::XMFLOAT3 &position);

	float getX() const;
	float getY() const;
	float getZ() const;
	DirectX::XMFLOAT3 getPosition() const;
private:
	DirectX::XMFLOAT3 m_position;
};
