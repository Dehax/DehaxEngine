#pragma once

#include <vector>

#include "Models\Model.h"

struct SimpleVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
};

class DEHAXENGINE_API DehaxEngine {
public:
	DehaxEngine(HWND hWnd);
	HRESULT InitDevice();
	void Render();

	inline void setModel(Model *model)
	{
		m_model = model;
	}
private:
	HRESULT CompileShaderFromFile(WCHAR *szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob **ppBlobOut);
	void CleanupDevice();

	HINSTANCE				m_hInst = nullptr;
	HWND					m_hWnd = nullptr;
	D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL		m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*			m_pd3dDevice = nullptr;
	ID3D11Device1*			m_pd3dDevice1 = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;
	ID3D11DeviceContext1*	m_pImmediateContext1 = nullptr;
	IDXGISwapChain*			m_pSwapChain = nullptr;
	IDXGISwapChain1*		m_pSwapChain1 = nullptr;
	ID3D11RenderTargetView*	m_pRenderTargetView = nullptr;
	ID3D11VertexShader*		m_pVertexShader = nullptr;
	ID3D11PixelShader*		m_pPixelShader = nullptr;
	ID3D11InputLayout*		m_pVertexLayout = nullptr;
	ID3D11Buffer*			m_pVertexBuffer = nullptr;
	ID3D11Buffer*			m_pIndexBuffer = nullptr;
	ID3D11Buffer*			m_pConstantBuffer = nullptr;
	DirectX::XMMATRIX		m_World;
	DirectX::XMMATRIX		m_View;
	DirectX::XMMATRIX		m_Projection;

	Model *m_model;
};
