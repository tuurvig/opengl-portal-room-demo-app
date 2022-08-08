//----------------------------------------------------------------------------------------
/**
 * \file       FreeCamera.hpp
 * \author     Richard Kvasnica
 * \brief      Free flying camera declaration
 *
 * Camera that can fly around in the scene
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "FirstPersonStaticCamera.hpp"

namespace kvasnric
{
	class FreeCamera final : public FirstPersonStaticCamera
	{
	public:
		FreeCamera(
			const glm::vec3& pos = CAMERA_START,
			float yaw = CAMERA_YAW_DEFAULT,
			float pitch = CAMERA_PITCH_DEFAULT,
			float sensitivity = CAMERA_SENSITIVITY,
			float movement = MOVEMENT_SPEED
		);

		~FreeCamera() override = default;

		/**
		 * Handles movement by inputed directions in the direction of already existing front and right vector of the camera.
		 */
		void UpdateMotion(float deltaTime, bool forward, bool backward, bool left, bool right);

		inline void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
	private:
		float m_MovementSpeed;
	};
}
