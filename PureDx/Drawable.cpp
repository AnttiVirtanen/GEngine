#include "pch.h"
#include "Drawable.h"

using namespace GEngine;
using namespace DirectX;

Drawable::Drawable() {
	m_worldTransformation = XMMatrixIdentity();
}

Drawable::Drawable(XMFLOAT3 position)
{
	m_worldTransformation = XMMatrixIdentity();
	transform(XMMatrixTranslation(position.x, position.y, position.z));
}

void Drawable::transform(XMMATRIX transformation)
{
	m_worldTransformation = m_worldTransformation * transformation;
}

unsigned int Drawable::vertexCount()
{
	return m_vertices.size();
}

unsigned int Drawable::indexCount()
{
	return m_indices.size();
}

vector<unsigned int> Drawable::getIndices()
{
	return m_indices;
}

// Reconsider this
vector<Vertex> Drawable::getVertices()
{
	vector<Vertex> transformed = m_vertices;
	for (auto &vertex: transformed) {
		XMVECTOR vertexVector = XMLoadFloat3(&vertex.pos);
		vertexVector = XMVector3Transform(vertexVector, getTransformation());
		XMStoreFloat3(&vertex.pos, vertexVector);
	}
	return transformed;
}

XMMATRIX Drawable::getTransformation()
{
	return m_worldTransformation;
}
