#include "..\stdafx.h"
#include "Vertex.h"

Vertex::Vertex()
	: Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f)
{
}

Vertex::Vertex(const float &x, const float &y, const float &z, const float &normalX, const float &normalY, const float &normalZ)
	: m_position(x, y, z), m_normal(normalX, normalY, normalZ)
{
}

Vertex::Vertex(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &normal)
	: m_position(position), m_normal(normal)
{
}

float Vertex::getX() const
{
	return m_position.x;
}

float Vertex::getY() const
{
	return m_position.y;
}

float Vertex::getZ() const
{
	return m_position.z;
}

DirectX::XMFLOAT3 Vertex::getPosition() const
{
	return m_position;
}

DirectX::XMFLOAT3 Vertex::getNormal() const
{
	return m_normal;
}
