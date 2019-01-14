#include "pch.h"
#include "Camera.h"
#include "Debugger.h"

using namespace GEngine;
using namespace DirectX;

Camera::Camera()
{
	*this = Camera(60, 1.3f, 1.0f, 1000.0f);
}

Camera::Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	m_aspectRatio = aspectRatio;
	m_fieldOfView = fieldOfView;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_position = XMVectorSet(0.0, 0, -2.0, 0);
	m_target = XMVectorSet(0, 0, 0, 0);
	m_up = XMVectorSet(0, 1, 0, 0);

	m_rotationMatrix = XMMatrixIdentity();
	m_translationMatrix = XMMatrixIdentity();
	
	m_theta = 1.5f * XM_PI;	// yaw l<->r
	m_phi = 0.25f * XM_PI; //pitch u<->d
}

XMMATRIX Camera::getPerspectiveTransformation()
{
	return XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fieldOfView), m_aspectRatio, m_nearPlane, m_farPlane);
}

XMMATRIX Camera::getProjectViewTransformation()
{
	return getCameraTransformation() * getPerspectiveTransformation();
}

// Move camera left <-> right. This might be wrong. 
void Camera::moveCamera(float x, float y, float z)
{
	m_translationMatrix = m_translationMatrix * XMMatrixTranslation(x, y, z);
}

void Camera::rotateCameraAroundYAxis(float angle)
{
	m_rotationMatrix = XMMatrixRotationY(angle);
}

void Camera::rotateCameraAroundXAxis(float angle)
{
	m_rotationMatrix = XMMatrixRotationY(angle);
}

// Method XMMatrixRotationRollPitchYaw might be suitable here
XMMATRIX Camera::getCameraTransformation()
{
	XMVECTOR translatedPosition = XMVector3Transform(m_position, m_translationMatrix);
	XMVECTOR translatedTarget = XMVector3Transform(m_target, m_translationMatrix);

	XMVECTOR targetAtOrigin = XMVectorSubtract(translatedTarget, translatedPosition);
	XMVECTOR targetRotated = XMVector3Transform(targetAtOrigin, m_rotationMatrix);

	XMVECTOR newRotatedTarget = XMVectorAdd(targetRotated, translatedPosition);
	
	//debug(translatedPosition, newRotatedTarget, m_up);

	return XMMatrixLookAtLH(translatedPosition, newRotatedTarget, m_up);
}

void Camera::debug(XMVECTOR pos, XMVECTOR tar, XMVECTOR up)
{
	XMFLOAT3 posx3;
	XMStoreFloat3(&posx3, pos);
	XMFLOAT3 upx3;
	XMStoreFloat3(&upx3, up);
	XMFLOAT3 tarx3;
	XMStoreFloat3(&tarx3, tar);

	Debugger::debugToConsole(
		"Camera pos: ",
		Debugger::toStr(posx3.x),
		Debugger::toStr(posx3.y),
		Debugger::toStr(posx3.z),
		"| Camera target: ",
		Debugger::toStr(tarx3.x),
		Debugger::toStr(tarx3.y),
		Debugger::toStr(tarx3.z),
		"| Camera up: ",
		Debugger::toStr(upx3.x),
		Debugger::toStr(upx3.y),
		Debugger::toStr(upx3.z)
	);
}



