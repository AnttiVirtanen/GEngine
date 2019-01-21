#pragma once
#include "Graphics.h"
#include <vector>

using namespace std;
using namespace DirectX;

// Should fillmode be here
namespace GEngine {
	class Mesh {
		public:
			Mesh();
			Mesh(MeshProto meshProto, XMFLOAT3 position = XMFLOAT3(0, 0, 0), D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID);

			void transform(XMMATRIX transformation);
			unsigned int vertexCount();
			unsigned int indexCount();
		
			vector<unsigned int> getIndices();
			vector<Vertex> getVertices();
			XMMATRIX getTransformation();
			D3D11_FILL_MODE getFillMode();
		private:
			D3D11_FILL_MODE m_fillMode;
			XMMATRIX m_worldTransformation;
			vector<unsigned int> m_indices;
			vector<Vertex> m_vertices;
	};
}
