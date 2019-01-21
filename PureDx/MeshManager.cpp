#include "pch.h"
#include "MeshManager.h"
#include <numeric>


void MeshManager::add(Mesh mesh)
{
	m_meshes.push_back(mesh);
}

unsigned int MeshManager::getTotalVertexCount()
{
	return std::accumulate(m_meshes.begin(), m_meshes.end(), 0, [](const int& x, Mesh& d) {
		return x + d.vertexCount();
	});
}

unsigned int MeshManager::getTotalIndexCount()
{
	return std::accumulate(m_meshes.begin(), m_meshes.end(), 0, [](const int& x, Mesh& d) {
		return x + d.indexCount();
	});
}

vector<unsigned int> MeshManager::getAllIndices()
{
	vector<unsigned int> indices;

	for (std::vector<Mesh>::iterator it = m_meshes.begin(); it != m_meshes.end(); it++) {
		vector<unsigned int> meshIndices = it->getIndices();
		indices.insert(indices.end(), meshIndices.begin(), meshIndices.end());
	}

	return indices;
}

vector<Mesh> MeshManager::getMeshes()
{
	return m_meshes;
}
