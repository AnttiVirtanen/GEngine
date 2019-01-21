#pragma once
#include <vector>

using std::vector;

// Separate rending and graphics card initialization.
namespace GEngine {
	class Renderer {

	public:
		Renderer(ID3D11Device1* device = nullptr, ID3D11DeviceContext1* context = nullptr) {
			m_device = device;
			m_context = context;
		}

		template <typename T> void render(vector<T> meshes, ID3D11Buffer* vBuffer) {
			int offsetIndex = 0;
			for(auto mesh: meshes) {
				vector<Vertex> vertices = mesh.getVertices();
				vector<unsigned int> indices = mesh.getIndices();
				D3D11_FILL_MODE fillMode = mesh.getFillMode();

				mapToBuffer(vBuffer, vertices.data(), sizeof(*vertices.data()) * mesh.vertexCount());
				CreateRenderStates(fillMode);
				m_context->RSSetState(m_rasterizerState.Get());

				m_context->DrawIndexed(mesh.indexCount(), offsetIndex, 0);
				offsetIndex = offsetIndex + mesh.indexCount();
			}
		}
		
		template <typename T> void mapToBuffer(ID3D11Buffer* buffer, T data, size_t size) {
			D3D11_MAPPED_SUBRESOURCE subResource;
			ZeroMemory(&subResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

			m_context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			memcpy(subResource.pData, data, size);
			m_context->Unmap(buffer, 0);
		}

		void setDevice(ID3D11Device1* device) {
			m_device = device;
		}

		void setContext(ID3D11DeviceContext1* context) {
			m_context = context;
		}

		// Rip programming
		void CreateRenderStates(D3D11_FILL_MODE fillMode) {
			D3D11_RASTERIZER_DESC rasterizerDesc;
			ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
			rasterizerDesc.FillMode = fillMode;
			rasterizerDesc.CullMode = D3D11_CULL_NONE;

			m_device->CreateRasterizerState(&rasterizerDesc, m_rasterizerState.GetAddressOf());
		}

		void Reset() {
			m_rasterizerState.Reset();
		}

	private:
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
		ID3D11Device1* m_device;
		ID3D11DeviceContext1* m_context;
	};
}

