//----------------------------------------------------------------------------------------
/**
 * \file       FirstPersonCamera.hpp
 * \author     Richard Kvasnica
 * \brief      FPS Camera declaration
 *
 * Camera handling walking around with inherited mouse movement
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "FirstPersonStaticCamera.hpp"

namespace kvasnric
{
	class FirstPersonCamera final : public FirstPersonStaticCamera
	{
	public:
		FirstPersonCamera(
			const glm::vec3& pos = CAMERA_START,
			float yaw = CAMERA_YAW_DEFAULT,
			float pitch = CAMERA_PITCH_DEFAULT,
			float sensitivity = CAMERA_SENSITIVITY
		);
		explicit FirstPersonCamera(const Camera& c, float sensitivity = CAMERA_SENSITIVITY);
		
		~FirstPersonCamera() override = default;

		/**
		 * Rotate the yaw angle of the camera
		 */
		void ChangeView(float angle);

		/**
		 * Update current camera position
		 */
		void UpdatePosition( 
			float deltaTime,
			float speed,
			float height,
			bool forward,
			bool left = false,
			bool right = false,
			bool backward = false );
		
	private:
	};
}
