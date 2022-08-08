//----------------------------------------------------------------------------------------
/**
 * \file       PredefinedCamera.hpp
 * \author     Richard Kvasnica
 * \brief      Predefined camera declaration
 *
 * Predefined camera that moves around a spline
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Camera.hpp"

#include <Scene/Spline.hpp>
#include <memory>

namespace kvasnric
{
	class PredefinedCamera final : public Camera
	{
	public:
		/**
		 * Constructor that takes in valid cyclic spline
		 */
		PredefinedCamera(std::shared_ptr<Spline> s);

		/**
		 * Sets the start time of the animation
		 */
		void Start(float time);

		/**
		 * Updates position and direction of the camera from the spline by time
		 */
		void Update(float time);
	private:
		std::shared_ptr<Spline> m_Spline;
		float m_StartTime;
	};
}