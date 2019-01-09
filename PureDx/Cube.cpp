#include "pch.h"
#include "Cube.h"

using namespace DirectX;

// Testing purposes.
Cube::Cube(XMFLOAT3 position) : Drawable(position) {
	m_indices = {
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
	m_vertices = {
		{XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},		// 0
		{XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},			// 1
		{XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},		// 2
		{XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},		// 3

		{XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},		// 4
		{XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},			// 5
		{XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},		// 6
		{XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)}			// 7
	};
}
