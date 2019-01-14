#pragma once
#include "Graphics.h"
#include <vector>

using namespace std;
using namespace DirectX;

namespace GEngine {
	class Mesh {
	public:
		Mesh();
		Mesh(XMFLOAT3 position);
		Mesh(vector<unsigned int> indices, vector<Vertex> vertices, XMFLOAT3 position = XMFLOAT3(0, 0, 0));

		void transform(XMMATRIX transformation);
		unsigned int vertexCount();
		unsigned int indexCount();
		
		vector<unsigned int> getIndices();
		vector<Vertex> getVertices();
		XMMATRIX getTransformation();
	protected:
		XMMATRIX m_worldTransformation;
		vector<unsigned int> m_indices;
		vector<Vertex> m_vertices;
	};
}
