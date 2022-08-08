//----------------------------------------------------------------------------------------
/**
 * \file       Spline.hpp
 * \author     Richard Kvasnica
 * \brief      Cyclic spline definition
*/
//----------------------------------------------------------------------------------------

#include "Spline.hpp"

namespace kvasnric
{
	Spline::Spline(const std::vector<glm::vec3>& points)
		: m_ControlPoints(points)
	{
	}

	Spline::Spline(std::vector<glm::vec3>&& points) noexcept
		: m_ControlPoints(std::move(points))
	{
	}

	glm::vec3 Spline::GetPosition(const float time) const
	{
		const int i = (int)time + m_ControlPoints.size();
		const float t = time - (int)time;
		
		const auto & P0 = m_ControlPoints[(i - 1) % m_ControlPoints.size()];
		const auto & P1 = m_ControlPoints[i % m_ControlPoints.size()];
		const auto & P2 = m_ControlPoints[(i + 1) % m_ControlPoints.size()];
		const auto & P3 = m_ControlPoints[(i + 2) % m_ControlPoints.size()];

		const float t2 = t * t;
		const float t3 = t * t2;
		
		return 0.5f * (P0 * (-t3 + 2.0f * t2 - t) + P1 * (3.0f * t3 - 5.0f * t2 + 2.0f)
			+ P2 * (-3.0f * t3 + 4.0f * t2 + t) + P3 * (t3 - t2));
	}

	glm::vec3 Spline::GetDirection(const float time) const
	{
		const int i = (int)time + m_ControlPoints.size();
		const float t = time - (int)time;

		const auto & P0 = m_ControlPoints[(i - 1) % m_ControlPoints.size()];
		const auto & P1 = m_ControlPoints[i % m_ControlPoints.size()];
		const auto & P2 = m_ControlPoints[(i + 1) % m_ControlPoints.size()];
		const auto & P3 = m_ControlPoints[(i + 2) % m_ControlPoints.size()];

		const float t2 = t * t;

		return 0.5f * (P0 * (-3.0f * t2 + 4.0f * t - 1.0f) + P1 * (9.0f*t2 - 10.0f*t)
			+ P2 * (-9.0f * t2 + 8.0f * t + 1.0f) + P3 * (3.0f * t2 - 2.0f * t));
	}

	void Spline::AddControlPoint(const glm::vec3& point)
	{
		m_ControlPoints.push_back(point);
	}
}
