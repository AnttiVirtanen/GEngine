#include "pch.h"
#include "Mesh.h"

using namespace GEngine;
using namespace DirectX;

Mesh::Mesh() {
	m_worldTransformation = XMMatrixIdentity();
}

Mesh::Mesh(XMFLOAT3 position)
{
	m_worldTransformation = XMMatrixIdentity();
	transform(XMMatrixTranslation(position.x, position.y, position.z));
}

Mesh::Mesh(vector<unsigned int> indices, vector<Vertex> vertices, XMFLOAT3 position) : Mesh(position)
{
	m_indices = indices;
	m_vertices = vertices;
}

void Mesh::transform(XMMATRIX transformation)
{
	m_worldTransformation = m_worldTransformation * transformation;
}

unsigned int Mesh::vertexCount()
{
	return m_vertices.size();
}

unsigned int Mesh::indexCount()
{
	return m_indices.size();
}

vector<unsigned int> Mesh::getIndices()
{
	return m_indices;
}

// Reconsider this
vector<Vertex> Mesh::getVertices()
{
	vector<Vertex> transformed = m_vertices;
	for (auto &vertex: transformed) {
		XMVECTOR vertexVector = XMLoadFloat3(&vertex.pos);
		vertexVector = XMVector3Transform(vertexVector, getTransformation());
		XMStoreFloat3(&vertex.pos, vertexVector);
	}
	return transformed;
}

XMMATRIX Mesh::getTransformation()
{
	return m_worldTransformation;
}
