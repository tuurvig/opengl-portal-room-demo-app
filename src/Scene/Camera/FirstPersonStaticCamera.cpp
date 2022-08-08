//----------------------------------------------------------------------------------------
/**
 * \file       FirstPersonStaticCamera.hpp
 * \author     Richard Kvasnica
 * \brief      FPS Static camera definition
 *
 * Camera locked in one place with enabled looking around with mouse movement
*/
//----------------------------------------------------------------------------------------

#include "FirstPersonStaticCamera.hpp"

namespace kvasnric
{
	FirstPersonStaticCamera::FirstPersonStaticCamera(
		const glm::vec3& pos,
		float yaw, float pitch, 
		float sensitivity
	)	: Camera( pos, WORLD_UP, yaw, pitch ), m_LookSensitivity( sensitivity )
	{
	}

	FirstPersonStaticCamera::FirstPersonStaticCamera(const Camera& c, const float sensitivity)
		: Camera(c), m_LookSensitivity(sensitivity)
	{
	}

	void FirstPersonStaticCamera::MouseMovement( const glm::vec2& offset )
	{
		auto const move = offset * m_LookSensitivity;
		m_Yaw += glm::radians(move.x);
		m_Pitch += glm::radians(move.y);
		
		m_Pitch = m_Pitch >  CAMERA_PITCH_CONSTRAINT ?  CAMERA_PITCH_CONSTRAINT :
				  m_Pitch < -CAMERA_PITCH_CONSTRAINT ? -CAMERA_PITCH_CONSTRAINT : m_Pitch;

		UpdateCameraSpace();
	}

}
