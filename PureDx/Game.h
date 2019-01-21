#pragma once
#include "StepTimer.h"
#include "Camera.h"
#include "Renderer.h"
#include "InputProxy.h"
#include "CameraController.h"
#include "MeshManager.h"
#include "MeshGenerator.h"

class Game {
public:

    Game() noexcept;

    void Initialize(HWND window, int width, int height);

    void Tick();

    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    void GetDefaultSize( int& width, int& height ) const;

	void onKeyDown(WPARAM wParam);
	void onMouseMove(WPARAM wParam, float xPosition, float yPosition);
	void onReleaseKey();

private:

    void Update(DX::StepTimer const& timer);
	void initializePipeline();
	XMMATRIX getWorldTransformation();
	ConstantBufferPerObject getConstantBufferObject();
	void Render();

    void Clear();
    void Present();

	void CreateBuffers();
    void CreateDevice();
    void CreateResources();
    void CreateRenderStates(D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID);

    void OnDeviceLost();

    HWND m_window;
    int m_outputWidth;
    int m_outputHeight;

    D3D_FEATURE_LEVEL m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;

    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// Testing purposes
	Camera m_camera;
	Renderer m_renderer;
	InputProxy* m_inputProxy;
	CameraController m_cameraController;
	MeshManager m_meshManager;
	MeshGenerator m_meshGenerator;

    DX::StepTimer                                   m_timer;
};