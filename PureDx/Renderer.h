#pragma once
#include <vector>

using std::vector;

namespace GEngine {
	template <typename T> class Renderer {
	public:
		void render(vector<T> meshes, ID3D11DeviceContext1* context, ID3D11Buffer* buffer) {
			for(auto mesh: meshes) {
				D3D11_MAPPED_SUBRESOURCE vertexSubResource;

				auto vertices = mesh.getVertices();

				context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vertexSubResource);
				memcpy(vertexSubResource.pData, vertices.data(), sizeof(*vertices.data()) * mesh.vertexCount());
				context->Unmap(buffer, 0);
				context->DrawIndexed(mesh.indexCount(), 0, 0);
			}
		}
	};
}

