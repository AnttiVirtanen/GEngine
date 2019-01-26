#pragma once

using namespace DirectX;

// Upright space might help 
namespace GEngine {
	class Camera {
	public:
		Camera();
		Camera(float fieldOfView, float aspectRatio, float nearPlane = 1.0f, float farPlane = 1000.0f);
		
		XMMATRIX getCameraTransformation();
		XMMATRIX getPerspectiveTransformation();
		XMMATRIX getProjectViewTransformation();

		void moveCameraHorizontally(float distance);
		void moveCameraVertically(float distance);

		void setCameraPosition(float x, float y, float z);
		void setCameraTarget(float x, float y, float z);

		void rotateCameraAroundYAxis(float angle);
		void rotateCameraAroundXAxis(float angle);

		XMVECTOR getLookAtVector();

		void debug(XMVECTOR pos, XMVECTOR tar, XMVECTOR up);
		// I guess we need a method to rotate around arbitrary axis, aight?
	private:
		float m_aspectRatio;
		float m_fieldOfView;
		float m_nearPlane;
		float m_farPlane;

		float m_phi;
		float m_theta;

		XMVECTOR m_position;
		XMVECTOR m_target;
		XMVECTOR m_up;

		XMMATRIX m_rotationMatrix;
	};
}

