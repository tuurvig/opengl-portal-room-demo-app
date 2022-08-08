//----------------------------------------------------------------------------------------
/**
 * \file       FirstPersonCamera.cpp
 * \author     Richard Kvasnica
 * \brief      FPS Camera definition
 *
 * Camera handling walking around with inherited mouse movement
*/
//----------------------------------------------------------------------------------------

#include "FirstPersonCamera.hpp"

namespace kvasnric
{
	FirstPersonCamera::FirstPersonCamera(
		const glm::vec3& pos,
		float yaw, float pitch,
		float sensitivity
	)	: FirstPersonStaticCamera( pos, yaw, pitch, sensitivity )
	{
	}

	FirstPersonCamera::FirstPersonCamera(const Camera& c, float sensitivity)
		: FirstPersonStaticCamera(c, sensitivity)
	{
	}

	void FirstPersonCamera::ChangeView(const float angle)
	{
		m_Yaw -= angle;
		UpdateCameraSpace();
	}

	void FirstPersonCamera::UpdatePosition(
		const float deltaTime, const float speed, const float height,
		const bool forward, const bool left, const bool right, const bool backward)
	{
		const glm::vec3 front = glm::normalize(glm::vec3(
			cos(m_Yaw),
			0,
			sin(m_Yaw))
		);
		
		const glm::vec3 r = glm::cross(front, WORLD_UP);
		
		const float velocity = speed * deltaTime;
		const auto frontAxis = front * velocity;
		const auto rightAxis = r * velocity;

		if ( forward ) m_Position += frontAxis;
		if ( backward ) m_Position -= frontAxis;
		if ( left ) m_Position -= rightAxis;
		if ( right ) m_Position += rightAxis;

		m_Position.y = height;
	}
	
}