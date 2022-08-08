//----------------------------------------------------------------------------------------
/**
 * \file       PredefinedCamera.cpp
 * \author     Richard Kvasnica
 * \brief      Predefined camera definition
 *
 * Predefined camera that moves around a spline
*/
//----------------------------------------------------------------------------------------

#include "PredefinedCamera.hpp"

namespace kvasnric
{
	PredefinedCamera::PredefinedCamera(std::shared_ptr<Spline> s)
		: Camera(), m_Spline(std::move(s)), m_StartTime(0.0f)
	{
		Update(0.0f);
	}

	void PredefinedCamera::Start(const float time)
	{
		m_StartTime = time;
		Update(0.0f);
	}

	void PredefinedCamera::Update(float time)
	{
		time = time - m_StartTime;
		// get position and direction from spline
		m_Position = m_Spline->GetPosition(time);
		m_Front = m_Spline->GetDirection(time);

		// update perpendicular vectors
		m_Right = glm::normalize(glm::cross(m_Front, WORLD_UP));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}
