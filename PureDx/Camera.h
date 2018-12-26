#pragma once

using namespace DirectX;

namespace GEngine {
	class Camera {
	public:
		Camera();
		Camera(float fieldOfView, float aspectRatio, float nearPlane = 1.0f, float farPlane = 1000.0f);
		
		XMMATRIX getCameraTransformation();
		XMMATRIX getPerspectiveTransformation();
		XMMATRIX getProjectViewTransformation();
		
		void setPosition(float x, float y, float z);
	private:
		float m_aspectRatio;
		float m_fieldOfView;
		float m_nearPlane;
		float m_farPlane;

		XMVECTOR m_position;
		XMVECTOR m_target;
		XMVECTOR m_up;
	};
}

