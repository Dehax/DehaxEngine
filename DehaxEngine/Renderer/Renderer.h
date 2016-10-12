#pragma once
#include "..\stdafx.h"

#include "Camera.h"

class DehaxEngine;

class DEHAXENGINE_API Renderer {
public:
	Renderer(DehaxEngine *engine);
	~Renderer();

	HRESULT InitDevice(HWND hWnd);
	void Render();

	Camera *getCamera() const;
private:
	struct SimpleVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
	};

	struct ConstantBuffer
	{
		DirectX::XMMATRIX mWorld;
		DirectX::XMMATRIX mView;
		DirectX::XMMATRIX mProjection;
		DirectX::XMFLOAT4 vLightDir;
		DirectX::XMFLOAT4 vLightColor;
	};

	//bool LoadShaderFromFile(LPCWSTR lpszFilePath, char **ppBlobOut, size_t &size);
	void CleanupDevice();

	DehaxEngine *m_engine = nullptr;
	Camera *m_camera = nullptr;

	HINSTANCE				m_hInst = nullptr;
	D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL		m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*			m_pd3dDevice = nullptr;
	ID3D11Device1*			m_pd3dDevice1 = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;
	ID3D11DeviceContext1*	m_pImmediateContext1 = nullptr;
	IDXGISwapChain*			m_pSwapChain = nullptr;
	IDXGISwapChain1*		m_pSwapChain1 = nullptr;
	ID3D11RenderTargetView*	m_pRenderTargetView = nullptr;
	ID3D11Texture2D*		m_pDepthStencil = nullptr;
	ID3D11DepthStencilView*	m_pDepthStencilView = nullptr;
	ID3D11VertexShader*		m_pVertexShader = nullptr;
	ID3D11PixelShader*		m_pPixelShader = nullptr;
	ID3D11InputLayout*		m_pVertexLayout = nullptr;
	ID3D11Buffer*			m_pVertexBuffer = nullptr;
	ID3D11Buffer*			m_pIndexBuffer = nullptr;
	ID3D11Buffer*			m_pConstantBuffer = nullptr;
};
