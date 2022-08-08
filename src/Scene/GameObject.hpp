//----------------------------------------------------------------------------------------
/**
 * \file       GameObject.hpp
 * \author     Richard Kvasnica
 * \brief      Game object class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Model.hpp"
#include <glm/glm.hpp>
#include <constants.hpp>

namespace kvasnric
{
	// Class that holds game object information in a scene
	class GameObject
	{
	public:
		/**
		 * GameObject constructor
		 * @param x shared pointer to an already constructed model
		 * @param pos position in world space
		 * @param model optional parameter. Custom model matrix from model space to world space. Default is unit matrix 4x4
		 */
		GameObject(std::shared_ptr<Model> x, const glm::vec3& pos, const glm::mat4& model = UNIT_MATRIX);

		/**
		 * Move constructor
		 * @param x r-value reference to a gameobject instance to be moved
		 */
		GameObject(GameObject&& x) noexcept;

		/**
		 * Copy constructor. Only shallow copy.
		 * @param x const reference to a gameobject instance to be copied
		 */
		GameObject(const GameObject& x) = default;

		/**
		 * Copy assignment operator
		 * @param x const reference to a gameobject instance to be copied to current instance
		 * @returns current gameobject instance reference
		 */
		GameObject& operator=(const GameObject& x);
		~GameObject() = default;

		/**
		 * Translate current object
		 * @param vec translation vector
		 * @returns current object reference
		 */
		GameObject& operator+=(const glm::vec3& vec);

		/**
		 * Create new GameObject by translating the object
		 * @param vec translation vector
		 * @returns new GameObject instance translated by vec
		 */
		GameObject operator+(const glm::vec3& vec) const;

		/**
		 * Translates gameobject in world space
		 * @param vec translation vector
		 * @returns current gameobject reference 
		 */
		inline GameObject& Translate(const glm::vec3& vec) { m_Position += vec; return *this; }

		/**
		 * Scales the object by applying scale to current model matrix
		 * @param scale scale vector parameteres
		 * @returns current gameobject reference
		 */
		GameObject& Scale(const glm::vec3& scale);

		/**
		 * Rotates the object by applying rotation to current model matrix by x axis
		 * @param angle angle of rotation
		 * @returns current gameobject reference
		 */
		GameObject& RotationXAxis(float angle);

		/**
		 * Rotates the object by applying rotation to current model matrix by y axis
		 * @param angle angle of rotation
		 * @returns current gameobject reference
		 */
		GameObject& RotationYAxis(float angle);

		/**
		 * Rotates the object by applying rotation to current model matrix by z axis
		 * @param angle angle of rotation
		 * @returns current gameobject reference
		 */
		GameObject& RotationZAxis(float angle);

		/**
		 * Reset gameobject model matrix to unit matrix
		 * @returns current gameobject reference
		 */
		GameObject& ResetAllTransforms();

		/**
		 * Sets position of the gameobject in world space
		 * @param pos position vector in world space
		 */
		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; }

		/**
		 * @returns position of the gameobject
		 */
		inline const glm::vec3 & GetPosition() const { return m_Position; }
		
		/**
		 * @returns current model matrix after applying translation to world position
		 */
		glm::mat4 GetModelMatrix() const;

		/**
		 * @returns Model instance of this game object
		 */
		inline const Model& GetModel() const { return *m_Model; }

		/**
		 * @param pos position in world coordinates
		 * @param proximity maximum distance position can be from the object
		 * @returns If the position in world coordinates is in proximity of the object.
		 */
		bool IsInProximity(const glm::vec3 & pos, float proximity) const;
	protected:
		std::shared_ptr<Model> m_Model;
		glm::mat4 m_ModelMatrix;
		glm::vec3 m_Position;

	};
}
