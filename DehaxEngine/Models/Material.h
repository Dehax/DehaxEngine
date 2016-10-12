#pragma once
#include "..\stdafx.h"

class DEHAXENGINE_API Material {
public:
	Material(const Material &material);
	Material(LPCWSTR vertexShaderBlobFile, LPCWSTR pixelShaderBlobFile, D3D11_INPUT_ELEMENT_DESC *layout, size_t layoutSize);
	Material(char *vertexShaderBlob, char *pixelShaderBlob, D3D11_INPUT_ELEMENT_DESC *layout, size_t layoutSize);
	~Material();

	static bool LoadShaderFromFile(LPCWSTR lpszFilePath, char **ppBlobOut, size_t &size);

	char *getVertexShaderBlob() const;
	size_t getVertexShaderSize() const;
	char *getPixelShaderBlob() const;
	size_t getPixelShaderSize() const;
	D3D11_INPUT_ELEMENT_DESC *getLayout() const;
	size_t getLayoutSize() const;

private:
	char *m_vertexShaderData;
	size_t m_vertexShaderSize;
	char *m_pixelShaderData;
	size_t m_pixelShaderSize;
	D3D11_INPUT_ELEMENT_DESC *m_layout;
	size_t m_layoutSize;
};
