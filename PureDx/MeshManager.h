#pragma once
#include "Mesh.h"

using namespace GEngine;

namespace GEngine {
	class MeshManager
	{
	public:
		void add(Mesh mesh);

		unsigned int getTotalVertexCount();
		unsigned int getTotalIndexCount();
		
		vector<unsigned int> getAllIndices();
		vector<Mesh> getMeshes();
	private:

		vector<Mesh> m_meshes;
	};
}


