//----------------------------------------------------------------------------------------
/**
 * \file       MovingObject.hpp
 * \author     Richard Kvasnica
 * \brief      Moving object child class of game object declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <Scene/GameObject.hpp>
#include <Scene/Spline.hpp>

namespace kvasnric
{
	// Creates game object with a functionality of moving along a spline
	class MovingObject final : public GameObject
	{
	public:
		MovingObject(std::shared_ptr<Model> x, std::shared_ptr<Spline> s);
		MovingObject(const GameObject& x, std::shared_ptr<Spline> s);

		/**
		 * Updates model matrix of a game object by computing position and direction on spline
		 */
		void Update(float time);
		inline const glm::vec3& GetDirection() const { return m_Direction; }
	private:
		std::shared_ptr<Spline> m_Spline;
		glm::vec3 m_Direction;
	};
}