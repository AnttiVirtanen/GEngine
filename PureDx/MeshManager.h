#pragma once
#include "Mesh.h"

using namespace GEngine;

namespace GEngine {
	class MeshManager
	{
	public:
		void add(Mesh mesh);
		void addRasterized(Mesh mesh);

		unsigned int getTotalVertexCount();
		unsigned int getTotalIndexCount();
		
		vector<unsigned int> getAllIndices();
		vector<Mesh> getMeshes();
		vector<Mesh> getRasterizedMeshes();
	private:
		unsigned int getVertexCountForCollection(vector<Mesh> collection);
		unsigned int getIndexCountForCollection(vector<Mesh> collection);
		vector<unsigned int> getIndicesForCollection(vector<Mesh> collection);

		vector<Mesh> m_meshes;
		vector<Mesh> m_rasterizedMesh;
	};
}


