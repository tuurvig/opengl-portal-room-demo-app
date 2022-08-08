//----------------------------------------------------------------------------------------
/**
 * \file       MountedCamera.hpp
 * \author     Richard Kvasnica
 * \brief      Mounted camera declaration
 *
 * Camera that mounts and pans around a game object.
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Camera.hpp"
#include <Scene/GameObject.hpp>

namespace kvasnric
{
	class MountedCamera final : public Camera
	{
	public:
		/**
		 * Constructor that takes in valid GameObject pointer
		 * so it can use virtual calls.
		 */
		MountedCamera(const GameObject * x);

		/**
		 * Handles updating yaw and pitch angles of the camera
		 */
		void MouseMovement(const glm::vec2& offset) override;

		/**
		 * Updates camera space by moving camera position by the direction of yaw and pitch angles from the gameobject position.
		 */
		void UpdateCameraSpace() override;
	private:
		
		const GameObject * m_Mount;
	};
}