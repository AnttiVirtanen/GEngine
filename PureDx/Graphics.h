#pragma once
#include "pch.h"

namespace GEngine {
	
	struct Vertex {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 col;
	};

	struct ConstantBufferPerObject {
		DirectX::XMMATRIX worldViewProjectMatrix;
	};
}
