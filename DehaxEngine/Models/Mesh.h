#pragma once
#include "..\stdafx.h"

#include <vector>

#include "Vertex.h"

class DEHAXENGINE_API Mesh {
public:
	Mesh();
	Mesh(const Mesh &mesh);

	unsigned int getNumVertices() const;
	unsigned int getNumFaces() const;
	
	Vertex &getVertex(const unsigned int index);
	DirectX::XMUINT3 &getFace(const unsigned int index);

	inline Mesh &Mesh::operator+=(const Vertex &v)
	{
		AddVertex(v);

		return *this;
	}

	void AddVertex(const Vertex &vertex);
	void AddFace(const DirectX::XMUINT3 &face);
	void ClearVertices();
	void ClearFaces();

private:
	std::vector<Vertex> m_vertices;
	std::vector<DirectX::XMUINT3> m_faces;
};
