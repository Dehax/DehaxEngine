#include "..\stdafx.h"
#include "Renderer.h"

#include <fstream>
#include "..\DehaxEngine.h"

Renderer::Renderer(DehaxEngine *engine)
	: m_engine(engine), m_camera(new Camera())
{
}

Renderer::~Renderer()
{
	CleanupDevice();
}

HRESULT Renderer::InitDevice(HWND hWnd)
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	m_camera->setWidth(width);
	m_camera->setHeight(height);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
							   D3D11_SDK_VERSION, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);

		if (hr == E_INVALIDARG) {
			// DirectX 11.0 платформы не распознают D3D_FEATURE_LEVEL_11_1, поэтому нужно попробовать без него
			hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
								   D3D11_SDK_VERSION, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
		}

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Получить DXGI factory устройства (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (SUCCEEDED(hr)) {
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr)) {
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}
	if (FAILED(hr))
		return hr;

	// Создать swap chain
	IDXGIFactory2* dxgiFactory2 = nullptr;
	hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
	if (dxgiFactory2) {
		// DirectX 11.1 или более новая версия
		hr = m_pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&m_pd3dDevice1));
		if (SUCCEEDED(hr)) {
			(void)m_pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_pImmediateContext1));
		}

		DXGI_SWAP_CHAIN_DESC1 sd;
		memset(&sd, 0, sizeof(sd));
		sd.Width = width;
		sd.Height = height;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;

		hr = dxgiFactory2->CreateSwapChainForHwnd(m_pd3dDevice, hWnd, &sd, nullptr, nullptr, &m_pSwapChain1);
		if (SUCCEEDED(hr)) {
			hr = m_pSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&m_pSwapChain));
		}

		dxgiFactory2->Release();
	} else {
		// DirectX 11.0 системы
		DXGI_SWAP_CHAIN_DESC sd;
		memset(&sd, 0, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		hr = dxgiFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain);
	}

	// Пока не перехватывается полный экран, поэтому блокируем сочетание Alt+Enter
	dxgiFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);

	dxgiFactory->Release();

	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return hr;

	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	memset(&descDepth, 0, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &m_pDepthStencil);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	memset(&descDSV, 0, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	// Установить окно просмотра
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &vp);

	return S_OK;
}

void Renderer::Render()
{
	HRESULT hr = S_OK;

	// Обновить время
	static float t = 0.0f;
	if (m_driverType == D3D_DRIVER_TYPE_REFERENCE) {
		t += (float)DirectX::XM_PI * 0.0125f;
	} else {
		static ULONGLONG timeStart = 0;
		ULONGLONG timeCur = GetTickCount64();

		if (timeStart == 0) {
			timeStart = timeCur;
		}

		t = (timeCur - timeStart) / 1000.0f;
	}

	// Инициализировать матрицы
	DirectX::XMVECTOR eyePosition = DirectX::XMLoadFloat3(&m_camera->getPosition());
	DirectX::XMVECTOR lookAt = DirectX::XMLoadFloat3(&m_camera->getLookAt());
	DirectX::XMVECTOR upVector = DirectX::XMLoadFloat3(&m_camera->getUp());
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eyePosition, lookAt, upVector);
	DirectX::XMMATRIX projectionMatrix;

	if (m_camera->getProjection() == Camera::Perspective) {
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(m_camera->getFOV(), m_camera->getWidth() / (FLOAT)m_camera->getHeight(), m_camera->getNearZ(), m_camera->getFarZ());
	} else {
		projectionMatrix = DirectX::XMMatrixOrthographicLH(m_camera->getWidth() / m_camera->getZoom(), m_camera->getHeight() / m_camera->getZoom(), m_camera->getNearZ(), m_camera->getFarZ());
	}

	// Очистить задний буфер
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::MidnightBlue);

	// Очистить буфер глубины значением 1.0 (максимальная глубина)
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Установить топологию
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Scene *scene = m_engine->getScene();
	unsigned int numObjects = scene->getNumObjects();

	for (unsigned int i = 0; i < numObjects; i++) {
		Model *model = (*scene)[i];
		Mesh *mesh = model->getMesh();

		// Создать вершинный буфер
		unsigned int numVertices = mesh->getNumVertices();
		SimpleVertex *vertices = new SimpleVertex[numVertices];

		for (unsigned int i = 0; i < numVertices; i++) {
			Vertex vertex = mesh->getVertex(i);
			vertices[i] = { vertex.getPosition(), vertex.getNormal() };
		}

		D3D11_BUFFER_DESC bd;
		memset(&bd, 0, sizeof(bd));

		// Создать константный буфер
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = m_pd3dDevice->CreateBuffer(&bd, nullptr, &m_pConstantBuffer);

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * numVertices;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		memset(&InitData, 0, sizeof(InitData));
		InitData.pSysMem = vertices;
		hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
		if (hr != S_OK) {
			MessageBoxW(nullptr, L"CreateBuffer() failed", L"ERROR", MB_OK);
		}
		delete[] vertices;

		// Установить вершинный буфер
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

		m_pVertexBuffer->Release();

		int numFaces = mesh->getNumFaces();

		// Создать индексный буфер
		WORD *indices = new WORD[numFaces * 3];

		for (int i = 0; i < numFaces; i++) {
			DirectX::XMUINT3 face = mesh->getFace(i);
			indices[i * 3] = face.x;
			indices[i * 3 + 1] = face.y;
			indices[i * 3 + 2] = face.z;
		}

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * numFaces * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, &m_pIndexBuffer);
		delete[] indices;

		// Установить индексный буфер
		m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		m_pIndexBuffer->Release();

		// ============================== SHADER ===========================================

		Material *material = model->getMaterial();

		char *pVSBlob = material->getVertexShaderBlob();
		size_t VSSize = material->getVertexShaderSize();

		// Создать вершинный шейдер
		hr = m_pd3dDevice->CreateVertexShader(pVSBlob, VSSize, nullptr, &m_pVertexShader);

		// Создать разметку входных данных вершинного шейдера
		hr = m_pd3dDevice->CreateInputLayout(material->getLayout(), material->getLayoutSize(), pVSBlob, VSSize, &m_pVertexLayout);

		// Установить разметку
		m_pImmediateContext->IASetInputLayout(m_pVertexLayout);

		char *pPSBlob = material->getPixelShaderBlob();
		size_t PSSize = material->getPixelShaderSize();

		// Создать пиксельный шейдер
		hr = m_pd3dDevice->CreatePixelShader(pPSBlob, PSSize, nullptr, &m_pPixelShader);
		// ============================== END SHADER =======================================

		ConstantBuffer cb;
		cb.mWorld = DirectX::XMMatrixTranspose(model->getWorldMatrix());
		//cb.mWorld = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(t));
		cb.mView = DirectX::XMMatrixTranspose(viewMatrix);
		cb.mProjection = DirectX::XMMatrixTranspose(projectionMatrix);
		DirectX::XMStoreFloat4(&cb.vLightDir, DirectX::XMVectorSubtract(eyePosition, lookAt));
		cb.vLightColor = DirectX::XMFLOAT4(model->getColor().f);

		m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &cb, 0, 0);

		m_pImmediateContext->VSSetShader(m_pVertexShader, nullptr, 0);
		m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pImmediateContext->PSSetShader(m_pPixelShader, nullptr, 0);
		m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pImmediateContext->DrawIndexed(numFaces * 3, 0, 0);

		m_pConstantBuffer->Release();
	}

	m_pSwapChain->Present(0, 0);
}

Camera *Renderer::getCamera() const
{
	return m_camera;
}

//bool Renderer::LoadShaderFromFile(LPCWSTR lpszFilePath, char **ppBlobOut, size_t &size)
//{
//	bool result = true;
//
//	std::ifstream shader_file(lpszFilePath, std::ios::in | std::ios::binary | std::ios::ate);
//	if (shader_file.good()) {
//		size = (size_t)shader_file.tellg();
//		*ppBlobOut = new char[size];
//		shader_file.seekg(0);
//		shader_file.read(*ppBlobOut, size);
//	} else {
//		result = false;
//	}
//
//	return result;
//}

void Renderer::CleanupDevice()
{
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain1) m_pSwapChain1->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pImmediateContext1) m_pImmediateContext1->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pd3dDevice1) m_pd3dDevice1->Release();
	if (m_pd3dDevice) m_pd3dDevice->Release();
}
