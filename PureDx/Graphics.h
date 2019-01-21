#pragma once
#include "pch.h"
#include <vector>

namespace GEngine {
	
	struct Vertex {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 col;
	};

	struct MeshProto {
		vector<unsigned int> indices;
		vector<Vertex> vertices;
	};

	struct ConstantBufferPerObject {
		DirectX::XMMATRIX worldViewProjectMatrix;
	};
}
