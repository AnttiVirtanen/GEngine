#pragma once
#include <vector>

using std::vector;

namespace GEngine {
	template <typename T> class Renderer {
	public:
		void addToBatch(T mesh) {
			m_batch.push_back(mesh);
		};

		void render(ID3D11DeviceContext1* context, ID3D11Buffer* buffer) {
			for(auto mesh: m_batch) {
				D3D11_MAPPED_SUBRESOURCE vertexSubResource;

				auto vertices = mesh.getVertices();

				context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vertexSubResource);
				memcpy(vertexSubResource.pData, vertices.data(), sizeof(*vertices.data()) * mesh.vertexCount());
				context->Unmap(buffer, 0);
				context->DrawIndexed(mesh.indexCount(), 0, 0);
			}
		}

	private:
		vector<T> m_batch;
	};
}

