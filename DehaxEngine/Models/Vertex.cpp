#include "..\stdafx.h"
#include "Vertex.h"

Vertex::Vertex()
	: Vertex(0.0f, 0.0f, 0.0f)
{
}

Vertex::Vertex(const float &x, const float &y, const float &z)
	: m_position(x, y, z)
{
}

Vertex::Vertex(const DirectX::XMFLOAT3 &position)
	: m_position(position)
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
