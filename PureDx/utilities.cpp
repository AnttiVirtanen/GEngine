#include "pch.h"
#include "utilities.h"

XMFLOAT3 GEngine::Utilities::XMVECTORToXMFLOAT3(XMVECTOR vector) {
	XMFLOAT3 floatx3;
	XMStoreFloat3(&floatx3, vector);
	return floatx3;
}
