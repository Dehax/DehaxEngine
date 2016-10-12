#include "..\stdafx.h"
#include "Material.h"

#include <fstream>

Material::Material(const Material &material)
{
	m_vertexShaderData = new char[material.m_vertexShaderSize];
	memcpy(m_vertexShaderData, material.m_vertexShaderData, material.m_vertexShaderSize);
	m_pixelShaderData = new char[material.m_pixelShaderSize];
	memcpy(m_pixelShaderData, material.m_pixelShaderData, material.m_pixelShaderSize);
	m_layout = new D3D11_INPUT_ELEMENT_DESC[material.m_layoutSize];
	memcpy(m_layout, material.m_layout, sizeof(D3D11_INPUT_ELEMENT_DESC) * material.m_layoutSize);
}

Material::Material(LPCWSTR vertexShaderBlobFile, LPCWSTR pixelShaderBlobFile, D3D11_INPUT_ELEMENT_DESC *layout, size_t layoutSize)
	: m_layout(new D3D11_INPUT_ELEMENT_DESC[layoutSize]), m_layoutSize(layoutSize)
{
	memcpy(m_layout, layout, sizeof(D3D11_INPUT_ELEMENT_DESC) * layoutSize);

	LoadShaderFromFile(vertexShaderBlobFile, &m_vertexShaderData, m_vertexShaderSize);
	LoadShaderFromFile(pixelShaderBlobFile, &m_pixelShaderData, m_pixelShaderSize);
}

Material::Material(char *vertexShaderBlob, char *pixelShaderBlob, D3D11_INPUT_ELEMENT_DESC *layout, size_t layoutSize)
	: m_vertexShaderData(vertexShaderBlob), m_pixelShaderData(pixelShaderBlob), m_layout(new D3D11_INPUT_ELEMENT_DESC[layoutSize]), m_layoutSize(layoutSize)
{
	memcpy(m_layout, layout, sizeof(D3D11_INPUT_ELEMENT_DESC) * layoutSize);
}

Material::~Material()
{
	if (m_vertexShaderData != nullptr) {
		delete[] m_vertexShaderData;
	}

	if (m_pixelShaderData != nullptr) {
		delete[] m_pixelShaderData;
	}

	if (m_layout != nullptr) {
		delete[] m_layout;
	}
}

bool Material::LoadShaderFromFile(LPCWSTR lpszFilePath, char **ppBlobOut, size_t &size)
{
	bool result = true;

	std::ifstream shader_file(lpszFilePath, std::ios::in | std::ios::binary | std::ios::ate);
	if (shader_file.good()) {
		size = (size_t)shader_file.tellg();
		*ppBlobOut = new char[size];
		shader_file.seekg(0);
		shader_file.read(*ppBlobOut, size);
	} else {
		result = false;
	}

	return result;
}

char *Material::getVertexShaderBlob() const
{
	return m_vertexShaderData;
}

size_t Material::getVertexShaderSize() const
{
	return m_vertexShaderSize;
}

char *Material::getPixelShaderBlob() const
{
	return m_pixelShaderData;
}

size_t Material::getPixelShaderSize() const
{
	return m_pixelShaderSize;
}

D3D11_INPUT_ELEMENT_DESC * Material::getLayout() const
{
	return m_layout;
}

size_t Material::getLayoutSize() const
{
	return m_layoutSize;
}
