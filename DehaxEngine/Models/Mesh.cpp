#include "..\stdafx.h"
#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh &mesh)
{
	m_vertices = mesh.m_vertices;
	m_faces = mesh.m_faces;
}

unsigned int Mesh::getNumVertices() const
{
	return m_vertices.size();
}

unsigned int Mesh::getNumFaces() const
{
	return m_faces.size();
}

Vertex &Mesh::getVertex(const unsigned int index)
{
	return m_vertices[index];
}

DirectX::XMUINT3 &Mesh::getFace(const unsigned int index)
{
	return m_faces[index];
}

void Mesh::AddVertex(const Vertex &vertex)
{
	float x = std::abs(vertex.getX());
	float y = std::abs(vertex.getY());
	float z = std::abs(vertex.getZ());

	m_vertices.push_back(vertex);
}

void Mesh::AddFace(const DirectX::XMUINT3 &face)
{
	m_faces.push_back(face);
}

void Mesh::ClearVertices()
{
	m_vertices.clear();
}

void Mesh::ClearFaces()
{
	m_faces.clear();
}
