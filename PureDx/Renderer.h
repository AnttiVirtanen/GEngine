#pragma once
#include <vector>

using std::vector;


namespace GEngine {
	class Renderer {
	public:

		template <typename T> void render(vector<T> meshes, ID3D11DeviceContext1* context, ID3D11Buffer* vBuffer) {
			int offsetIndex = 0;
			for(auto mesh: meshes) {
				vector<Vertex> vertices = mesh.getVertices();
				vector<unsigned int> indices = mesh.getIndices();

				mapToBuffer(context, vBuffer, vertices.data(), sizeof(*vertices.data()) * mesh.vertexCount());
				
				context->DrawIndexed(mesh.indexCount(), offsetIndex, 0);
				offsetIndex = offsetIndex + mesh.indexCount();
			}
		}
		
		template <typename T> void mapToBuffer(ID3D11DeviceContext1* context, ID3D11Buffer* buffer, T data, size_t size) {
			D3D11_MAPPED_SUBRESOURCE subResource;
			ZeroMemory(&subResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

			context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			memcpy(subResource.pData, data, size);
			context->Unmap(buffer, 0);
		}
	};
}

