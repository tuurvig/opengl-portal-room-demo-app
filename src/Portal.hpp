//----------------------------------------------------------------------------------------
/**
 * \file       Portal.hpp
 * \author     Richard Kvasnica
 * \brief      Portal class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <glm/glm.hpp>
#include <Scene/Texture.hpp>
#include <Renderer/VertexArray.hpp>

namespace kvasnric
{
	// Implements the functionality of a portal
	class Portal
	{
	public:
		/**
		 * Constructs portal
		 * @param texture dynamic texture of the portal (blue or orange)
		 * @param position position of the portal
		 * @param direction in which direction is portal facing
		 */
		Portal(std::shared_ptr<Texture2D> texture, const glm::vec3& position, const glm::vec3& direction);
		void Bind() const;

		/**
		 * Calculates teleportation matrix that aligns the world into the look of this portal
		 * @param other other portal that will be linked to this portal
		 * @returns angle between the portals
		 */
		float SetTeleporation(const Portal& other);

		/**
		 * Transforms a vector by the teleportation matrix
		 */
		glm::vec3 Teleport(const glm::vec4& x) const;

		/**
		 * @returns whether the position in world coordinates collides with the portal
		 */
		bool IsColliding(const glm::vec3 & x) const;

		/**
		 * Change the position and direction of the portal
		 */
		void ModifyPortal(const glm::vec3& position, const glm::vec3& direction);

		// getters
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetDirection() const { return m_Direction; }
		
		inline float GetViewAngle() const { return m_View; }
		inline const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		inline const glm::mat4& GetTeleportation() const { return m_TeleportationMatrix; }
		inline const VertexArray& GetVAO() const { return *m_VAO; }
		inline unsigned IndicesCount() const { return m_Indices; }
	private:
		void InitPortalMesh();

		/**
		 * @param newDir new direction which the portal should be facing
		 * @returns a signed angled between the original direction and the new direction
		 */
		float PlaneDirection(const glm::vec3 &newDir) const;

		std::unique_ptr<VertexArray> m_VAO;
		unsigned char m_Indices;
		float m_View;
		
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		
		glm::mat4 m_RotationMatrix;
		glm::mat4 m_ModelMatrix;
		glm::mat4 m_ModelInverse;
		glm::mat4 m_TeleportationMatrix;
		glm::mat4 m_TeleportationInverse;
	};
}