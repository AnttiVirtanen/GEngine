#pragma once

#include "Mesh.h"

using namespace GEngine;

namespace GEngine {
	class MeshGenerator
	{
	public:
		static Mesh generateStaticCube(XMFLOAT3 position = XMFLOAT3(0, 0, 0));
		static Mesh generateStaticGrid(XMFLOAT3 position = XMFLOAT3(0, 0, 0));
	};
}

