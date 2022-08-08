//----------------------------------------------------------------------------------------
/**
 * \file       Camera.cpp
 * \author     Richard Kvasnica
 * \brief      Camera abstract definition
 *
 * Basic functionality of a virtual camera
*/
//----------------------------------------------------------------------------------------

#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


namespace kvasnric
{
	Camera::Camera(const glm::vec3& pos, const glm::vec3& up, float yaw, float pitch)
		: m_Position(pos), m_Front(CAMERA_FRONT), m_Up(up), m_Right(WORLD_RIGHT)
		, m_Yaw(glm::radians(yaw)), m_Pitch(glm::radians(pitch)), m_FOV(CAMERA_FOV_DEFAULT)
	{
		UpdateCameraSpace();
	}

	void Camera::Teleport(const glm::vec3& pos)
	{
		m_Position = pos;
	}

	void Camera::SetViewDirection(const glm::vec3& dir)
	{
		m_Front = dir;
		m_Right = glm::normalize(glm::cross(m_Front, WORLD_UP));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void Camera::UpdateCameraSpace()
	{
		m_Front = glm::normalize(glm::vec3(
			cos(m_Yaw) * cos(m_Pitch),
			sin(m_Pitch),
			sin(m_Yaw) * cos(m_Pitch)
		));

		m_Right = glm::normalize(glm::cross(m_Front, WORLD_UP));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::MouseMovement(const glm::vec2& offset)
	{
	}

	glm::mat4 Camera::GetProjectionMatrix(const float width, const float height, const float near, const float far) const
	{
		return glm::perspective(glm::radians(m_FOV), width / height, near, far);
	}

}