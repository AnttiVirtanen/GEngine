#include "pch.h"
#include "Camera.h"
#include "Debugger.h"
#include "utilities.h"

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
	
	m_theta = 1.5f * XM_PI;	// yaw l<->r
	m_phi = 0.25f * XM_PI; //pitch u<->d
}

void Camera::setCameraPosition(float x, float y, float z) {
	m_position = XMVectorSet(x, y, z, 0);
}

void GEngine::Camera::setCameraTarget(float x, float y, float z) {
	m_target = XMVectorSet(x, y, z, 0);
}

XMMATRIX Camera::getPerspectiveTransformation()
{
	return XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fieldOfView), m_aspectRatio, m_nearPlane, m_farPlane);
}

XMMATRIX Camera::getProjectViewTransformation()
{
	return getCameraTransformation() * getPerspectiveTransformation();
}

XMVECTOR GEngine::Camera::getLookAtVector() {
	XMVECTOR lookAtVector = XMVectorSubtract(m_target, m_position);
	XMVECTOR lookAtVectorNormalized = XMVector3Normalize(lookAtVector);
	return XMVector3Transform(lookAtVectorNormalized, m_rotationMatrix);
}

void GEngine::Camera::moveCameraHorizontally(float distance) {
	XMVECTOR lookAtVectorRotated = getLookAtVector();

	XMVECTOR directionVector = XMVector3Cross(m_up, lookAtVectorRotated);
	XMVECTOR directionVectorNormalized = XMVector3Normalize(directionVector);
	
	XMVECTOR upVector = XMVector3Cross(directionVectorNormalized, lookAtVectorRotated);

	directionVectorNormalized = directionVectorNormalized * distance;
	
	m_target = m_target + directionVectorNormalized;
	m_position = m_position + directionVectorNormalized;
}

// This is bad.
void GEngine::Camera::moveCameraVertically(float distance) {
	XMVECTOR lookAtVectorRotated = getLookAtVector();
	XMFLOAT3 x3 = Utilities::XMVECTORToXMFLOAT3(lookAtVectorRotated);
	XMVECTOR projectionVector = XMVectorSet(x3.x, 0, x3.z, 1);
	XMVECTOR scaledProjectionVector = projectionVector * distance;
	
	m_target = XMVectorAdd(m_target, scaledProjectionVector);
	m_position = XMVectorAdd(m_position, scaledProjectionVector);
}

void Camera::rotateCameraAroundYAxis(float angle)
{
	m_rotationMatrix = XMMatrixRotationY(angle);
}

void Camera::rotateCameraAroundXAxis(float angle)
{
	m_rotationMatrix = XMMatrixRotationX(angle);
}

// Method XMMatrixRotationRollPitchYaw might be suitable here
XMMATRIX Camera::getCameraTransformation()
{
	XMVECTOR lookAtVectorRotated = getLookAtVector();
	XMVECTOR newTarget = XMVectorAdd(lookAtVectorRotated, m_position);
	
	debug(m_position, newTarget, m_up);

	return XMMatrixLookAtLH(m_position, newTarget, m_up);
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
