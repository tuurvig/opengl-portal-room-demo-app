//----------------------------------------------------------------------------------------
/**
 * \file       MountedCamera.cpp
 * \author     Richard Kvasnica
 * \brief      Mounted camera definition
 *
 * Camera that mounts and pans around a game object.
*/
//----------------------------------------------------------------------------------------

#include "MountedCamera.hpp"

namespace kvasnric
{
	MountedCamera::MountedCamera(const GameObject * x)
		: Camera(), m_Mount(x)
	{
		UpdateCameraSpace();
	}

	void MountedCamera::MouseMovement(const glm::vec2& offset)
	{
		const auto move = offset;
		m_Yaw += glm::radians(offset.x) * 0.15f;
		m_Pitch -= glm::radians(offset.y) * 0.15f;

		m_Pitch = m_Pitch > CAMERA_PITCH_CONSTRAINT ? CAMERA_PITCH_CONSTRAINT :
			m_Pitch < -CAMERA_PITCH_CONSTRAINT ? -CAMERA_PITCH_CONSTRAINT : m_Pitch;
		
		UpdateCameraSpace();
	}

	void MountedCamera::UpdateCameraSpace()
	{
		// act as if the game object was the camera that faces some direction
		m_Front = glm::normalize(glm::vec3(
			cos(m_Yaw) * cos(m_Pitch),
			sin(m_Pitch),
			sin(m_Yaw) * cos(m_Pitch)
		));

		// shift camera position from gameobject position by the direction vector
		m_Position = m_Mount->GetPosition() + 2.0f*m_Front;

		// reverse the look vector so the shifted camera faces the object.
		m_Front = -m_Front;

		// update perpendicular vectors
		m_Right = glm::normalize(glm::cross(m_Front, WORLD_UP));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}
