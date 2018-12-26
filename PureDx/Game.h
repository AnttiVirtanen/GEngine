#pragma once
#include "StepTimer.h"
#include "Cube.h"
#include "Camera.h"

class Game {
public:

    Game() noexcept;

    void Initialize(HWND window, int width, int height);

    void Tick();

    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
	void initializePipeline();
	void CreateVertexBufferAndCopyVertices();
    void Render();

    void Clear();
    void Present();

	void CreateBuffers();
    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;

    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>		m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			m_indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			m_constantBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_inputLayout;

	// Testing purposes
	Cube m_cube;
	Camera m_camera;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};