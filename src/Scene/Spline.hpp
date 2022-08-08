//----------------------------------------------------------------------------------------
/**
 * \file       Spline.hpp
 * \author     Richard Kvasnica
 * \brief      Cyclic spline declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace kvasnric
{
	// Catmull-Rom cyclic spline
	class Spline
	{
	public:
		Spline() = default;
		// spline is constructed by vec3 points in world space
		Spline(const std::vector<glm::vec3>& points);
		Spline(std::vector<glm::vec3>&& points) noexcept;

		~Spline() = default;

		/**
		 * Computes a position on the spline by time
		 */
		glm::vec3 GetPosition(float time) const;

		/**
		 * Compute a direction on the spline by time
		 */
		glm::vec3 GetDirection(float time) const;

		/**
		 * Adds one control point at the end of spline vector
		 */
		void AddControlPoint(const glm::vec3 & point);
	private:
		std::vector<glm::vec3> m_ControlPoints;
	};
}