#pragma once
#include "Graphics.h"
#include <vector>

using namespace std;
using namespace DirectX;

namespace GEngine {
	class Drawable {
	public:
		Drawable();
		Drawable(XMFLOAT3 position);

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
