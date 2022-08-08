//----------------------------------------------------------------------------------------
/**
 * \file       GameObject.cpp
 * \author     Richard Kvasnica
 * \brief      Game object class definition
*/
//----------------------------------------------------------------------------------------

#include "GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>


namespace kvasnric
{
	GameObject::GameObject(std::shared_ptr<Model> x, const glm::vec3& pos, const glm::mat4& model)
		: m_Model(std::move(x)), m_ModelMatrix(model), m_Position(pos)
	{
	}

	GameObject::GameObject(GameObject&& x) noexcept
		: m_Model(std::move(x.m_Model)), m_ModelMatrix(x.m_ModelMatrix), m_Position(x.m_Position)
	{
	}

	GameObject& GameObject::operator=(const GameObject& x)
	{
		if (&x != this)
		{
			m_Model = x.m_Model;
			m_ModelMatrix = x.m_ModelMatrix;
			m_Position = x.m_Position;
		}
		return *this;
	}

	GameObject& GameObject::operator+=(const glm::vec3& vec)
	{
		return Translate(vec);
	}

	GameObject GameObject::operator+(const glm::vec3& vec) const
	{
		return GameObject(m_Model, m_Position + vec, m_ModelMatrix);
	}

	glm::mat4 GameObject::GetModelMatrix() const
	{
		/**
		 * internal model matrix is always without translation.
		 * Translation is always done at the end, when asking the object about the final model matrix.
		 */
		return glm::translate(UNIT_MATRIX, m_Position) * m_ModelMatrix;
	}

	bool GameObject::IsInProximity(const glm::vec3& pos, const float proximity) const
	{
		// makes a distance vector.
		const auto dist = m_Position - pos;

		// checks if square value of distance is less than a proximity
		return dist.x * dist.x + dist.y * dist.y + dist.z * dist.z < proximity * proximity;
	}

	GameObject& GameObject::Scale(const glm::vec3& scale)
	{
		m_ModelMatrix = glm::scale(UNIT_MATRIX, scale) * m_ModelMatrix;
		return *this;
	}

	GameObject& GameObject::RotationXAxis(float angle)
	{
		m_ModelMatrix = glm::rotate(UNIT_MATRIX, glm::radians(angle), X_AXIS) * m_ModelMatrix;
		return *this;
	}

	GameObject& GameObject::RotationYAxis(float angle)
	{
		m_ModelMatrix = glm::rotate(UNIT_MATRIX, glm::radians(angle), Y_AXIS) * m_ModelMatrix;
		return *this;
	}

	GameObject& GameObject::RotationZAxis(float angle)
	{
		m_ModelMatrix = glm::rotate(UNIT_MATRIX, glm::radians(angle), Z_AXIS) * m_ModelMatrix;
		return *this;
	}

	GameObject& GameObject::ResetAllTransforms()
	{
		m_ModelMatrix = UNIT_MATRIX;
		return *this;
	}

}