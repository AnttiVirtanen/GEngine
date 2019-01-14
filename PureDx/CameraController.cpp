#include "pch.h"
#include "CameraController.h"
#include "InputProxy.h"

using namespace GEngine;

CameraController::CameraController(Camera* camera)
{
	m_camera = camera;
	m_cameraSpeed = 0.1f;
	m_xRotation = 0.0f;
	m_yRotation = 0.0f;
	updateCursorPosition(0, 0);
}

void CameraController::handleKeyboardInput(CONTROLS controlKey)
{
	switch (controlKey) {
		case CONTROLS::leftArrow:
			m_camera->moveCamera(-m_cameraSpeed, 0.0f, 0.0f);
			break;
		case CONTROLS::rightArrow:
			m_camera->moveCamera(m_cameraSpeed, 0.0f, 0.0f);
			break;
		case CONTROLS::upArrow:
			m_camera->moveCamera(0.0f, 0.0f, m_cameraSpeed);
			break;
		case CONTROLS::downArrow:
			m_camera->moveCamera(0.0f, 0.0f, -m_cameraSpeed);
			break;
	}
}

void CameraController::handleCursorMovement(float x, float y)
{
	if (x < m_lastCursorX) {
		m_xRotation += m_cameraSpeed;
		m_camera->rotateCameraAroundYAxis(m_xRotation);
	}

	if (x > m_lastCursorX) {
		m_xRotation -= m_cameraSpeed;
		m_camera->rotateCameraAroundYAxis(m_xRotation);
	}

	if (y < m_lastCursorY) {
		m_yRotation += m_cameraSpeed;
		//m_camera->rotateCameraAroundXAxis(m_yRotation);
	}

	if (y > m_lastCursorY) {
		m_yRotation -= m_cameraSpeed;
		//m_camera->rotateCameraAroundXAxis(m_yRotation);
	}

	updateCursorPosition(x, y);
}

void CameraController::updateCursorPosition(float x, float y)
{
	m_lastCursorX = x;
	m_lastCursorY = y;
}

