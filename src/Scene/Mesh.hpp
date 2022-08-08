//----------------------------------------------------------------------------------------
/**
 * \file       Mesh.hpp
 * \author     Richard Kvasnica
 * \brief      Mesh class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <glm/glm.hpp>
#include <Renderer/VertexArray.hpp>
#include "Material.hpp"

namespace kvasnric
{
	/**
	 * One vertex always has a position, normal, texcoord and a tangent
	 */
	struct Vertex
	{
		Vertex();
		Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex, const glm::vec3& tan);
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
	};

	class Mesh
	{
	public:
		Mesh();
		Mesh(Mesh&& x) noexcept;
		~Mesh() = default;

		/**
		 * Adds one vertex into the vertex vector
		 */
		void AddVertex(const Vertex& vert);
		
		/**
		 * Adds one vertex index into the element vector
		 */
		void AddVertexIndex(uint32_t index);

		/**
		 * Adds three indices into the element vector at once.
		 */
		void AddFace(uint32_t v1, uint32_t v2, uint32_t v3);

		/**
		 * Assigns a material to this mesh.
		 */
		void AssignMaterial(std::unique_ptr<Material>&& m) noexcept;

		/**
		 * Needs to called every time a mesh is complete. Creates VAO and sends the vertex and elements data into shader.
		 */
		void RegisterMesh();

		/**
		 * Binds this mesh's VAO.
		 */
		void Bind() const;

		/**
		 * Goes through all the faces and finds the intersection point with an inputted direction vector.
		 * @param out output parameter of resulting intersection point, will be left out if no intersection was found
		 * @param normal output parameter of intersecting face's normal, will be left out if no intersection was found
		 * @param origin origin of direction in world coordinates
		 * @param direction direction in world coordinates
		 * @returns bool whether an intersection was found. If there are multiple intersections, the closest one will be a result.
		 */
		bool FindIntersection(glm::vec3& out, glm::vec3 & normal, const glm::vec3& origin, const glm::vec3& direction) const;

		/**
		 * Möller–Trumbore intersection algorithm
		 * @param out output parameter of resulting intersection point, will be left out if no intersection was found
		 * @param origin origin of direction in model coordinates
		 * @param direction direction in world coordinates
		 * @param triangleId id of an index in elements vector
		 * @returns bool whether an intersection was found.
		 */
		bool Intersects(glm::vec3& out, const glm::vec3& origin, const glm::vec3& direction, unsigned triangleId) const;

		/**
		 * @returns number of how many indices mesh has
		 */
		inline uint32_t GetCountOfIndices() const { return m_Indices.size(); }

		/**
		 * @returns A mesh's material
		 */
		inline const Material& GetMaterial() const { return *m_Material; }

		void Export() const;
	protected:
		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<Material> m_Material;

		bool m_Finalized;
	};
}
