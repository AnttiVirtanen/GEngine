#include "pch.h"
#include "Cube.h"

using namespace DirectX;

// Testing purposes.
Cube::Cube(XMFLOAT3 position) : Drawable(position) {
	m_indices = {
		0, 1, 2,
		1, 3, 2,
		4, 5, 6,
		5, 7, 6,
		4, 5, 0,
		5, 2, 0,
		6, 7, 2,
		7, 3, 2,
		4, 0, 6,
		0, 2, 6,
		1, 5, 3,
		5, 7, 3
	};
	m_vertices = {
		{XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},

		{XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)}
	};
}
