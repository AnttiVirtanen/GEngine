#pragma once
#include "Drawable.h"

using namespace GEngine;

namespace GEngine {
	class Cube : public Drawable {
	public:
		Cube(XMFLOAT3 position = XMFLOAT3(0, 0, 0));
	};
}

