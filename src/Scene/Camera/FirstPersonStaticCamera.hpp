//----------------------------------------------------------------------------------------
/**
 * \file       FirstPersonStaticCamera.hpp
 * \author     Richard Kvasnica
 * \brief      FPS Static camera declaration
 *
 * Camera locked in one place with enabled looking around with mouse movement
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Camera.hpp"

namespace kvasnric
{
	class FirstPersonStaticCamera : public Camera
	{
	public:
		FirstPersonStaticCamera(
			const glm::vec3& pos = CAMERA_START,
			float yaw = CAMERA_YAW_DEFAULT,
			float pitch = CAMERA_PITCH_DEFAULT,
			float sensitivity = CAMERA_SENSITIVITY
		);

		explicit FirstPersonStaticCamera(const Camera& c, float sensitivity = CAMERA_SENSITIVITY);
		~FirstPersonStaticCamera() override = default;

		void MouseMovement(const glm::vec2& offset) override;
	protected:
		float m_LookSensitivity;
	};
}

