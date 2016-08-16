#pragma once
#include "..\stdafx.h"

#include <vector>

#include "Vertex.h"

class DEHAXENGINE_API Mesh {
public:
	explicit Mesh();
	explicit Mesh(const Mesh &mesh);

	int getNumVertices() const;
	int getNumFaces() const;
	
	Vertex getVertex(const int index) const;
	DirectX::XMUINT3 getFace(const int index) const;

	void AddVertex(const Vertex &vertex);
	void AddFace(const DirectX::XMUINT3 &face);
	void ClearVertices();
	void ClearFaces();

private:
	std::vector<Vertex> m_vertices;
	std::vector<DirectX::XMUINT3> m_faces;
};
