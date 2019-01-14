#include "pch.h"
#include "MeshManager.h"
#include <numeric>

// This is bad


void MeshManager::add(Mesh mesh)
{
	m_meshes.push_back(mesh);
}

void MeshManager::addRasterized(Mesh mesh)
{
	m_rasterizedMesh.push_back(mesh);
}

unsigned int MeshManager::getTotalVertexCount()
{
	return getVertexCountForCollection(m_meshes) + getVertexCountForCollection(m_rasterizedMesh);
}

unsigned int MeshManager::getTotalIndexCount()
{
	return getIndexCountForCollection(m_meshes) + getIndexCountForCollection(m_rasterizedMesh);
}

vector<unsigned int> MeshManager::getAllIndices()
{
	vector<unsigned int> indices = getIndicesForCollection(m_meshes);
	vector<unsigned int> indicesRasterized = getIndicesForCollection(m_rasterizedMesh);
	indices.insert(indices.end(), indicesRasterized.begin(), indicesRasterized.end());
	
	return indices;
}

unsigned int MeshManager::getVertexCountForCollection(vector<Mesh> collection)
{
	return std::accumulate(collection.begin(), collection.end(), 0, [](const int& x, Mesh& d) {
		return x + d.vertexCount();
	});
}

unsigned int MeshManager::getIndexCountForCollection(vector<Mesh> collection)
{
	return std::accumulate(collection.begin(), collection.end(), 0, [](const int& x, Mesh& d) {
		return x + d.indexCount();
	});
}

vector<unsigned int> MeshManager::getIndicesForCollection(vector<Mesh> collection)
{
	vector<unsigned int> indices;

	for (std::vector<Mesh>::iterator it = collection.begin(); it != collection.end(); it++) {
		vector<unsigned int> meshIndices = it->getIndices();
		indices.insert(indices.end(), meshIndices.begin(), meshIndices.end());
	}

	return indices;
}


vector<Mesh> MeshManager::getMeshes()
{
	return m_meshes;
}

vector<Mesh> MeshManager::getRasterizedMeshes()
{
	return m_rasterizedMesh;
}
