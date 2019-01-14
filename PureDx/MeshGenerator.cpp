#include "pch.h"
#include "MeshGenerator.h"


Mesh MeshGenerator::generateStaticCube(XMFLOAT3 position)
{
	vector<unsigned int> m_indices = {
		0, 1, 2,			// Front face
		1, 3, 2,			// Front face

		5, 4, 6,			// Back face
		5, 6, 7,			// Back face

		4, 5, 0,			// Top face
		5, 1, 0,			// Top face

		2, 3, 6,			// Bottom face
		3, 7, 6,			// Bottom face

		4, 0, 6,			// Left Face
		0, 2, 6,			// Left Face

		1, 5, 3,			// Right Face
		5, 7, 3				// Right Face
	};

	vector<Vertex> m_vertices = {
		{XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},		// 0
		{XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},			// 1
		{XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},		// 2
		{XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},		// 3

		{XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},		// 4
		{XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},			// 5
		{XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},		// 6
		{XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)}			// 7
	};

	return Mesh(m_indices, m_vertices, position);
}

Mesh MeshGenerator::generateStaticGrid(XMFLOAT3 position)
{
	int verticalBlocks = 4;
	int horizontalBlocks = 4;

	vector<unsigned int> indices;

	for (int y = 0; y < verticalBlocks; y++) {
		for (int x = 0; x < horizontalBlocks; x++) {
			// First half
			unsigned int topLeft = x + ((horizontalBlocks + 1) * y);
			unsigned int topRight = topLeft + horizontalBlocks + 1;
			unsigned int bottomLeft = topLeft + 1;
			indices.push_back(topLeft);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			// Second half
			unsigned int bottomRight = topRight + 1;
			indices.push_back(topRight);
			indices.push_back(bottomRight);
			indices.push_back(bottomLeft);
		}
	}

	vector<Vertex> vertices;
	for (int y = 0; y <= verticalBlocks; y++) {
		for (int x = horizontalBlocks; x >= 0; x--) {
			Vertex vertex = { XMFLOAT3(0.5f * y, 0.5f * x, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f) };
			vertices.push_back(vertex);
		}
	}

	return Mesh(indices, vertices, position);
}
