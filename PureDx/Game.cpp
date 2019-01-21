#include "pch.h"
#include "Game.h"
#include "Graphics.h"
#include "Debugger.h"

#include <d3dcompiler.h>

#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>


// Since d3dcompiler.lib is not directly added as dependency to linker add it manually
#pragma comment(lib,"d3dcompiler.lib")

extern void ExitGame();

using namespace DirectX;
using namespace std;
using namespace GEngine;
using Microsoft::WRL::ComPtr;

Game::Game() noexcept : m_window(nullptr), m_outputWidth(800),
m_outputHeight(600), m_featureLevel(D3D_FEATURE_LEVEL_9_1) {

	m_inputProxy = InputProxy::getInstance();
	m_camera = Camera(60, static_cast<float>(m_outputWidth / m_outputHeight));
	m_cameraController = CameraController(&m_camera);
	m_renderer = Renderer(m_d3dDevice.Get(), m_d3dContext.Get());

	m_camera.setCameraPosition(0, 2.5f, -5.0f);

	// Test models.
	MeshProto m1 = m_meshGenerator.generateStaticCube();
	MeshProto m2 = m_meshGenerator.generateStaticCube();
	MeshProto m3 = m_meshGenerator.generateStaticCube();
	
	MeshProto r1 = m_meshGenerator.generateStaticGrid();

	m_meshManager.add(Mesh(m1, XMFLOAT3(-3.0, 0.5, 0.5)));
	m_meshManager.add(Mesh(m2, XMFLOAT3(-1.0, 0.5, 0)));
	m_meshManager.add(Mesh(m3, XMFLOAT3(1.0, 0.5, 0)));
	m_meshManager.add(Mesh(r1, XMFLOAT3(-2.0, 0, 0), D3D11_FILL_WIREFRAME));
}

void Game::Initialize(HWND window, int width, int height)
{
	m_window = window;
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);

	CreateDevice();

	CreateResources();
	initializePipeline();
	CreateBuffers();
	m_renderer.setDevice(m_d3dDevice.Get());
	m_renderer.setContext(m_d3dContext.Get());
}

void Game::Tick()
{
	m_timer.Tick([&]() { Update(m_timer); });
	Render();
}

void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());
}

void Game::initializePipeline() {
	ID3DBlob *vertexShaderBlob, *pixelShaderBlob;

	D3DCompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &vertexShaderBlob, 0);
	D3DCompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &pixelShaderBlob, 0);

	m_d3dDevice->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, m_vertexShader.GetAddressOf());
	m_d3dDevice->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, m_pixelShader.GetAddressOf());

	m_d3dContext->VSSetShader(m_vertexShader.Get(), 0, 0);
	m_d3dContext->PSSetShader(m_pixelShader.Get(), 0, 0);

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	m_d3dDevice->CreateInputLayout(inputElementDesc, 2, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &m_inputLayout);
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());
}

void Game::CreateBuffers() {
	int totalVertexCount = m_meshManager.getTotalVertexCount();
	int totalIndexCount = m_meshManager.getTotalIndexCount();
	vector<unsigned int> indices = m_meshManager.getAllIndices();

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(GEngine::Vertex) * totalVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * totalIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(GEngine::ConstantBufferPerObject);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData;
	indexBufferData.pSysMem = &indices[0];
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;

	m_d3dDevice->CreateBuffer(&vertexBufferDesc, nullptr, m_vertexBuffer.GetAddressOf());
	m_d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, m_constantBuffer.GetAddressOf());
	m_d3dDevice->CreateBuffer(&indexBufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
}

void Game::onMouseMove(WPARAM wParam, float xPosition, float yPosition) {
	switch (wParam) {
	case MK_LBUTTON:
		m_cameraController.handleCursorMovement(xPosition, yPosition);
		break;
	default:
		m_cameraController.updateCursorPosition(0, 0);
		break;
	}
}

void Game::onKeyDown(WPARAM wParam) {
	CONTROLS controlKey = static_cast<CONTROLS>(wParam);

	m_inputProxy->setControlKey(controlKey);
	m_cameraController.handleKeyboardInput(controlKey);
}

void Game::onReleaseKey()
{
	m_inputProxy->releaseControl();
}

// Scene method
XMMATRIX Game::getWorldTransformation() {
	//float elapsedTime = float(m_timer.GetTotalSeconds());
	//XMMATRIX worldTranformation = DirectX::XMMatrixRotationX(XMConvertToRadians(elapsedTime * 10));
	
	XMMATRIX cameraTransformation = m_camera.getProjectViewTransformation();
	XMMATRIX worldTranformation = DirectX::XMMatrixRotationY(XMConvertToRadians(0));
	XMMATRIX transformation = worldTranformation * cameraTransformation;
	
	return transformation;
}

// Scene method
ConstantBufferPerObject Game::getConstantBufferObject() {
	XMMATRIX transformation = getWorldTransformation();
	ConstantBufferPerObject cbpo;
	cbpo.worldViewProjectMatrix = DirectX::XMMatrixTranspose(transformation);

	return cbpo;
}

void Game::Render()
{
	if (m_timer.GetFrameCount() == 0) { return; }
	
	Clear();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	m_d3dContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	m_d3dContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	m_d3dContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ConstantBufferPerObject cbpo = getConstantBufferObject();

	m_renderer.mapToBuffer(m_constantBuffer.Get(), &cbpo, sizeof(cbpo));

	m_renderer.render(m_meshManager.getMeshes(), m_vertexBuffer.Get());

	Present();
}

void Game::Clear()
{
	m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::Black);
	m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
	m_d3dContext->RSSetViewports(1, &viewport);

}

void Game::Present()
{
	HRESULT hr = m_swapChain->Present(1, 0);

	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
		OnDeviceLost();
	}
	else {
		DX::ThrowIfFailed(hr);
	}
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();
}

void Game::OnWindowSizeChanged(int width, int height)
{
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);

	CreateResources();
}

void Game::GetDefaultSize(int& width, int& height) const
{
	width = 800;
	height = 600;
}

void Game::CreateDevice()
{
	static const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	DX::ThrowIfFailed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		0, &featureLevel, 1, D3D11_SDK_VERSION, device.ReleaseAndGetAddressOf(),
		&m_featureLevel, context.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(device.As(&m_d3dDevice));
	DX::ThrowIfFailed(context.As(&m_d3dContext));
}

void Game::CreateResources()
{
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
	m_renderTargetView.Reset();
	m_depthStencilView.Reset();
	m_d3dContext->Flush();

	UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
	UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	UINT backBufferCount = 2;

	if (m_swapChain)
	{
		HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			OnDeviceLost();
			return;
		}
		else
		{
			DX::ThrowIfFailed(hr);
		}
	}
	else
	{
		ComPtr<IDXGIDevice1> dxgiDevice;
		DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

		ComPtr<IDXGIAdapter> dxgiAdapter;
		DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

		ComPtr<IDXGIFactory2> dxgiFactory;
		DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = backBufferWidth;
		swapChainDesc.Height = backBufferHeight;
		swapChainDesc.Format = backBufferFormat;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = backBufferCount;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
			m_d3dDevice.Get(), m_window, &swapChainDesc, &fsSwapChainDesc,
			nullptr, m_swapChain.ReleaseAndGetAddressOf()));

		DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
	}

	ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

	DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

	CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

	ComPtr<ID3D11Texture2D> depthStencil;
	DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));
}

void Game::OnDeviceLost()
{
	m_depthStencilView.Reset();
	m_renderTargetView.Reset();
	m_swapChain.Reset();
	m_d3dContext.Reset();
	m_d3dDevice.Reset();
	m_pixelShader.Reset();
	m_vertexShader.Reset();
	m_indexBuffer.Reset();
	m_vertexBuffer.Reset();

	m_renderer.Reset();

	CreateDevice();
	CreateResources();
	initializePipeline();
}