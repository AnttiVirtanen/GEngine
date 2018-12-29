#pragma once
#include <vector>

using std::vector;

namespace GEngine {
	class Renderer {
	public:
		template <typename T> void render(vector<T> meshes, ID3D11DeviceContext1* context, ID3D11Buffer* buffer) {
			for(auto mesh: meshes) {
				auto vertices = mesh.getVertices();
				mapToBuffer(context, buffer, vertices.data(), sizeof(*vertices.data()) * mesh.vertexCount());
				context->DrawIndexed(mesh.indexCount(), 0, 0);
			}
		}
		
		template <typename T> void mapToBuffer(ID3D11DeviceContext1* context, ID3D11Buffer* buffer, T data, size_t size) {
			D3D11_MAPPED_SUBRESOURCE subResource;

			context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			memcpy(subResource.pData, data, size);
			context->Unmap(buffer, 0);
		}
	};
}

