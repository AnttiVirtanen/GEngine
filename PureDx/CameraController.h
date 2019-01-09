#pragma once
#include "Camera.h"
#include "InputProxy.h"

using namespace GEngine;

namespace GEngine {
	class CameraController {
	public:
		CameraController(Camera* camera = nullptr);

		void handleKeyboardInput(CONTROLS controlKey);
		void handleCursorMovement(float x, float y);
		void updateCursorPosition(float x, float y);
	private:
		Camera* m_camera;
		
		float m_cameraSpeed;

		float m_lastCursorX;
		float m_lastCursorY;

		float m_xRotation;
		float m_yRotation;
	};
}