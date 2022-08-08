//----------------------------------------------------------------------------------------
/**
 * \file       MovingObject.hpp
 * \author     Richard Kvasnica
 * \brief      Moving object child class of game object definition
*/
//----------------------------------------------------------------------------------------

#include "MovingObject.hpp"

#include <constants.hpp>

namespace kvasnric
{
	MovingObject::MovingObject(std::shared_ptr<Model> x, std::shared_ptr<Spline> s)
		: GameObject(std::move(x), glm::vec3(0.0f)), m_Spline(std::move(s))
	{
	}

	MovingObject::MovingObject(const GameObject& x, std::shared_ptr<Spline> s)
		: GameObject(x), m_Spline(std::move(s))
	{
	}

	void MovingObject::Update(const float time)
	{
		m_Position = m_Spline->GetPosition(time);
		m_Direction = glm::normalize(m_Spline->GetDirection(time));

		const glm::vec3 & z = m_Direction;
		const glm::vec3 x = glm::normalize(glm::cross(WORLD_UP, z));
		const glm::vec3 y = glm::normalize(glm::cross(z, x));
		
		m_ModelMatrix = {
			x.x, x.y, x.z, 0.0f,
			y.x, y.y, y.z, 0.0f,
			z.x, z.y, z.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}
}
