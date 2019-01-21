#pragma once

#include "Mesh.h"
#include "Graphics.h"

using namespace GEngine;

namespace GEngine {
	class MeshGenerator
	{
	public:
		static MeshProto generateStaticCube();
		static MeshProto generateStaticGrid(int horizontalBlocks = 100, int verticalBlocks = 100);
	};
}

