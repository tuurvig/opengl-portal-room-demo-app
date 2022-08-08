//----------------------------------------------------------------------------------------
/**
 * \file       FreeCamera.cpp
 * \author     Richard Kvasnica
 * \brief      Free flying camera definition
 *
 * Camera that can fly around in the scene
*/
//----------------------------------------------------------------------------------------

#include "FreeCamera.hpp"

namespace kvasnric
{
	FreeCamera::FreeCamera(
		const glm::vec3& pos,
		float yaw, float pitch,
		float sensitivity, float speed
	)	: FirstPersonStaticCamera( pos, yaw, pitch, sensitivity ), m_MovementSpeed( speed )
	{
	}

	void FreeCamera::UpdateMotion( float deltaTime, bool forward, bool backward, bool left, bool right )
	{
		UpdateCameraSpace();
		
		const float velocity = m_MovementSpeed * deltaTime;
		const auto frontAxis = m_Front * velocity;
		const auto rightAxis = m_Right * velocity;

		if ( forward ) m_Position += frontAxis;
		if ( backward ) m_Position -= frontAxis;
		if ( left ) m_Position -= rightAxis;
		if ( right ) m_Position += rightAxis;
	}

	
}