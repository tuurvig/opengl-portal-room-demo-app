//----------------------------------------------------------------------------------------
/**
 * \file       Portal.cpp
 * \author     Richard Kvasnica
 * \brief      Portal class definition
*/
//----------------------------------------------------------------------------------------

#include "Portal.hpp"

#include <constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace kvasnric
{
	Portal::Portal(std::shared_ptr<Texture2D> texture, const glm::vec3& position, const glm::vec3& direction)
		: m_VAO(nullptr), m_Indices(0), m_Texture(std::move(texture)), m_Position(position), m_Direction({ 0.0f, 0.0f, 1.0f })
		, m_RotationMatrix(UNIT_MATRIX), m_ModelMatrix(UNIT_MATRIX), m_ModelInverse(UNIT_MATRIX)
		, m_TeleportationMatrix(UNIT_MATRIX), m_TeleportationInverse(UNIT_MATRIX)
	{
		const float angle = PlaneDirection(glm::normalize(direction));
		m_Direction = direction;
		m_RotationMatrix = glm::rotate(UNIT_MATRIX, angle, glm::vec3(0.0f, 1.0f, 0.0f));

		InitPortalMesh();
	}

	void Portal::Bind() const
	{
		m_Texture->Bind();
	}

	float Portal::PlaneDirection(const glm::vec3& newDir) const
	{
		// computes angle between two vectors
		const float angle = glm::acos(glm::dot(m_Direction, newDir));

		// if y component of the normal of those two vectors is negative it should be left handed rotation.  
		if (glm::cross(m_Direction, newDir).y < 0) return -angle;
		return angle;
	}


	float Portal::SetTeleporation(const Portal& other)
	{
		// get the signed angle
		const float angle = PlaneDirection(other.m_Direction);

		// create the world rotation matrix that will align those two portals
		const glm::mat4 rotation =
			glm::rotate(UNIT_MATRIX, -angle, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(UNIT_MATRIX, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// new viewing angle from the different point of view
		m_View = angle + glm::radians(180.0f);

		// calculate new position of the other portal when the entire world rotated
		const glm::vec3 newPos = rotation * glm::vec4(other.m_Position, 1.0f );

		// translate the rotated world from the new calculated other portal position to this portal's position 
		m_TeleportationMatrix = glm::translate(UNIT_MATRIX, m_Position - newPos) * rotation;

		// create the inverse teleportation matrix that will be used to transform position vectors into the other portal
		m_TeleportationInverse = glm::inverse(m_TeleportationMatrix);

		return glm::abs(angle);
	}

	void Portal::ModifyPortal(const glm::vec3& position, const glm::vec3& direction)
	{
		// portal to be slightly closer to the camera than the wall.
		m_Position = position + direction * 0.01f;

		// get signed angle between the new direction and the current direction 
		const float angle = PlaneDirection(direction);

		// update the direction
		m_Direction = direction;

		// rotate with the rotation matrix
		m_RotationMatrix = glm::rotate(UNIT_MATRIX, angle, glm::vec3(0.0f, 1.0f, 0.0f)) * m_RotationMatrix;

		// translate rotation matrix to the portals new position
		m_ModelMatrix = glm::translate(UNIT_MATRIX, m_Position) * m_RotationMatrix;

		// calculate inverse model matrix that will be used for calculating collisions
		m_ModelInverse = glm::inverse(m_ModelMatrix);
	}

	glm::vec3 Portal::Teleport(const glm::vec4& x) const
	{
		return m_TeleportationInverse * x;
	}

	bool Portal::IsColliding(const glm::vec3& x) const
	{
		// position in world coordinates to be transformed into portal coordinates
		const glm::vec3 pos = m_ModelInverse * glm::vec4(x, 1.0f);
		
		return glm::abs(pos.x) < 0.5f && glm::abs(pos.y) < 0.9f && pos.z < 0.001f;
	}

	void Portal::InitPortalMesh()
	{
		const int vertsCnt = 46 * 3;
		
		const float verts[vertsCnt] = {
			-0.340215f, 0.748323f,	-0.01f,
			-0.234344f, 0.831492f,	-0.01f,
			0.340215f, 0.748323f,	-0.01f,
			-0.119468f, 0.882707f,	-0.01f,
			0.000000f, 0.900000f,	-0.01f,
			0.119468f, 0.882707f,	-0.01f,
			0.234345f, 0.831492f,	-0.01f,
			0.340215f, 0.748323f,	-0.01f,
			-0.234344f, 0.831492f,	-0.01f,
			-0.119468f, 0.882707f,	-0.01f,
			0.234345f, 0.831492f,	-0.01f,
			0.433012f, 0.636396f,	-0.01f,
			-0.433012f, 0.636396f,	-0.01f,
			0.509168f, 0.500013f,	-0.01f,
			-0.509168f, 0.500013f,	-0.01f,
			0.565757f, 0.344415f,	-0.01f,
			0.600605f, 0.175581f,	-0.01f,
			-0.565757f, 0.344415f,	-0.01f,
			-0.509168f, 0.500013f,	-0.01f,
			0.612371f, 0.000000f,	-0.01f,
			-0.612371f, 0.00000f,	-0.01f,
			0.600605f, -0.175581f,	-0.01f,
			-0.600605f, -0.175581f,	-0.01f,
			0.565757f, -0.344415f,	-0.01f,
			0.509168f, -0.500013f,	-0.01f,
			-0.565757f, -0.344415f, -0.01f,
			0.433012f, -0.636396f,	-0.01f,
			-0.433012f, -0.636396f, -0.01f,
			0.340215f, -0.748323f,	-0.01f,
			-0.340215f, -0.748323f, -0.01f,
			0.234344f, -0.831492f,	-0.01f,
			0.119468f, -0.882707f,	-0.01f,
			-0.234344f, -0.831492f, -0.01f,
			-0.340215f, -0.748323f, -0.01f,
			0.234344f, -0.831492f,	-0.01f,
			-0.234344f, -0.831492f, -0.01f,
			0.119468f, -0.882707f,	-0.01f,
			0.000000f, -0.900000f,	-0.01f,
			-0.119467f, -0.882707f, -0.01f,
			-0.433012f, -0.636396f, -0.01f,
			0.433012f, -0.636396f,	-0.01f,
			-0.509167f, -0.500013f, -0.01f,
			0.509168f, -0.500013f,	-0.01f,
			-0.600605f, 0.175581f,	-0.01f,
			-0.433012f, 0.636396f,	-0.01f,
			0.433012f, 0.636396f,	-0.01f,
		};
		
		const int indicesCnt = 90;
		m_Indices = indicesCnt;
		const unsigned indices[indicesCnt] = {
			0, 1, 2,
			3, 4, 5,
			5, 6, 3,
			6, 7, 8,
			9, 10, 1,
			7, 11, 12,
			11, 13, 14,
			13, 15, 14,
			15, 16, 17,
			18, 15, 17,
			16, 19, 20,
			19, 21, 22,
			21, 23, 22,
			23, 24, 25,
			22, 23, 25,
			24, 26, 27,
			26, 28, 29,
			28, 30, 29,
			30, 31, 32,
			33, 34, 35,
			36, 37, 38,
			38, 35, 36,
			33, 39, 40,
			39, 41, 42,
			41, 25, 24,
			22, 20, 19,
			20, 43, 16,
			43, 17, 16,
			18, 44, 45,
			44, 0, 2
		};

		m_VAO.reset(new VertexArray());
		m_VAO->Bind();
		m_VAO->SetVertexBuffer(std::make_unique<VertexBuffer>(verts, sizeof(verts), DRAW::STATIC));
		m_VAO->SetElementBuffer(std::make_unique<ElementBuffer>(indices, sizeof(indices), DRAW::STATIC));

		m_VAO->EnableVertexAttrib(POSITION_LOC);
		m_VAO->SetVertexAttribPointer(POSITION_LOC, 0, 3 * sizeof(float));
	}
}
