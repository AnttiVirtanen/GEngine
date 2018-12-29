#include "pch.h"
#include "Camera.h"

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
	m_position = XMVectorSet(0, 0, 0, 0);
	m_target = XMVectorSet(0, 0, 0, 0);
	m_up = XMVectorSet(0, 1, 0, 0);
}

XMMATRIX Camera::getPerspectiveTransformation()
{
	return XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fieldOfView), m_aspectRatio, m_nearPlane, m_farPlane);
}

XMMATRIX Camera::getProjectViewTransformation()
{
	return getCameraTransformation() * getPerspectiveTransformation();
}

void Camera::setPosition(float x, float y, float z)
{
	m_position = XMVectorSet(x, y, z, 0);
}

void Camera::moveCamera(float x, float y, float z)
{
	m_position = m_position + XMVectorSet(x, y, z, 0);
}

XMMATRIX Camera::getCameraTransformation()
{
	return XMMatrixLookAtLH(m_position, m_target, m_up);
}
