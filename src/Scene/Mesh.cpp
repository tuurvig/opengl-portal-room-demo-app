//----------------------------------------------------------------------------------------
/**
 * \file       Mesh.cpp
 * \author     Richard Kvasnica
 * \brief      Mesh class definition
*/
//----------------------------------------------------------------------------------------

#include "Mesh.hpp"
#include <Renderer/Buffer.hpp>

#include <constants.hpp>

namespace kvasnric
{
	Vertex::Vertex()
		: Position(ZERO_VECTOR), Normal(ZERO_VECTOR), TexCoords(ZERO_VEC2), Tangent(ZERO_VECTOR)
	{
	}

	Vertex::Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex, const glm::vec3& tan)
		: Position(pos), Normal(normal), TexCoords(tex), Tangent(tan)
	{
	}


	Mesh::Mesh()
		: m_VAO(nullptr), m_Material(nullptr), m_Finalized(false)
	{
	}

	Mesh::Mesh(Mesh&& x) noexcept
		: m_Vertices(std::move(x.m_Vertices))
		, m_Indices(std::move(x.m_Indices))
		, m_VAO(std::move(x.m_VAO))
		, m_Material(std::move(x.m_Material))
		, m_Finalized(x.m_Finalized)
	{
	}
	
	void Mesh::Bind() const
	{
		m_VAO->Bind();
		m_Material->Bind();
	}

	bool Mesh::FindIntersection(glm::vec3& out, glm::vec3& normal, const glm::vec3& origin, const glm::vec3& direction) const
	{
		bool intersects = false;
		for (unsigned i = 0; i < m_Indices.size(); i+=3)
		{
			// give intersection into temp value and check if the new intersection is closer than the already found one. 
			glm::vec3 temp;
			if (Intersects(temp, origin, direction, i) && (!intersects || (temp.x*temp.x + temp.y*temp.y + temp.z*temp.z) < (out.x*out.x + out.y*out.y + out.z*out.z)))
			{
				intersects = true;
				out = temp;
				normal = m_Vertices[m_Indices[i]].Normal;
			}
		}

		return intersects;
	}

	// Inspired from wikipedias pseudo-code.
	bool Mesh::Intersects(glm::vec3& out, const glm::vec3& origin, const glm::vec3& direction, unsigned triangleId) const
	{
		const float EPS = 0.0000001f;

		const glm::vec3& v0 = m_Vertices[m_Indices[triangleId]].Position;
		const glm::vec3& v1 = m_Vertices[m_Indices[triangleId + 1]].Position;
		const glm::vec3& v2 = m_Vertices[m_Indices[triangleId + 2]].Position;

		const glm::vec3 edge1 = v1 - v0;
		const glm::vec3 edge2 = v2 - v0;

		const glm::vec3 h = glm::cross(direction, edge2);
		const float a = glm::dot(edge1, h);

		// checks whether the two direction vectors are parallel
		if (a > -EPS && a < EPS) return false;

		const float f = 1.0f / a;

		const glm::vec3 s = origin - v0;

		const float u = f * glm::dot(s, h);

		// direction faces in the opposite way from triangle
		if (u < 0.0f || u > 1.0f) return false;

		const glm::vec3 q = glm::cross(s, edge1);

		const float v = f * glm::dot(direction, q);

		if (v < 0.0f || u + v > 1.0f) return false;

		const float t = f * glm::dot(edge2, q);

		// ray intersection
		if (t > EPS)
		{
			out = origin + direction * t;
			return true;
		}
		
		return false;
		
	}

	void Mesh::AssignMaterial(std::unique_ptr<Material>&& m) noexcept
	{
		m_Material = std::move(m);
	}

	void Mesh::AddVertex(const Vertex& vert)
	{
		m_Vertices.emplace_back(vert);
	}

	void Mesh::AddVertexIndex(uint32_t index)
	{
		m_Indices.emplace_back(index);
	}

	void Mesh::AddFace(uint32_t v1, uint32_t v2, uint32_t v3)
	{
		m_Indices.emplace_back(v1);
		m_Indices.emplace_back(v2);
		m_Indices.emplace_back(v3);
	}

	void Mesh::RegisterMesh()
	{
		m_VAO = std::make_unique<VertexArray>();

		m_VAO->SetVertexBuffer(std::make_unique<VertexBuffer>(
			m_Vertices.data(), m_Vertices.size() * sizeof(Vertex), DRAW::STATIC));

		m_VAO->SetElementBuffer(std::make_unique<ElementBuffer>(
			m_Indices.data(), m_Indices.size() << 2, DRAW::STATIC));

		m_VAO->EnableVertexAttrib(POSITION_LOC);
		m_VAO->SetVertexAttribPointer(POSITION_LOC, offsetof(Vertex, Position), sizeof(Vertex));

		m_VAO->EnableVertexAttrib(NORMAL_LOC);
		m_VAO->SetVertexAttribPointer(NORMAL_LOC, offsetof(Vertex, Normal), sizeof(Vertex));

		m_VAO->EnableVertexAttrib(TEX_COORD_LOC);
		m_VAO->SetVertexAttribPointer(TEX_COORD_LOC, offsetof(Vertex, TexCoords), sizeof(Vertex));

		m_VAO->EnableVertexAttrib(TANGENT_LOC);
		m_VAO->SetVertexAttribPointer(TANGENT_LOC, offsetof(Vertex, Tangent), sizeof(Vertex));

		m_Finalized = true;
	}

	void Mesh::Export() const
	{
		FILE *f;
		fopen_s(&f, "exported.txt", "w");
		//std::ofstream file("portal_exported.txt");

		if (f != nullptr)
		{
			fprintf(f, "Vertices: position, normal, texCoord\n");
			fprintf(f, "Vertex count: %u\n", m_Vertices.size());
			fprintf(f, " = {\n");
			const std::string delim = ", ";
			//const std::string delimF = "f, ";
			for (const auto & x : m_Vertices)
			{
				fprintf(f, "%s, %s, %s, %s, %s, %s, %s, %s,\n",
					std::to_string(x.Position.x).c_str(),
					std::to_string(x.Position.y).c_str(),
					std::to_string(x.Position.z).c_str(),
					std::to_string(x.Normal.x).c_str(),
					std::to_string(x.Normal.y).c_str(),
					std::to_string(x.Normal.z).c_str(),
					std::to_string(x.TexCoords.x).c_str(),
					std::to_string(x.TexCoords.y).c_str());
					//std::to_string(x.Tangent.x).c_str(),
					//std::to_string(x.Tangent.y).c_str(),
					//std::to_string(x.Tangent.z).c_str());
			}

			fprintf(f, "};\n");

			fprintf(f, "Indices: 3 indices per face\n");
			fprintf(f, "Vertex count: %u\n", m_Indices.size());
			fprintf(f, " = {\n");

			//file << "};" << std::endl << std::endl;
			//
			//file << "Indices: 3 indices per face" << std::endl;
			//file << "Indices count: " << m_Indices.size() << std::endl;
			//file << " = {" << std::endl;

			for (unsigned i = 0; i < m_Indices.size(); i += 3)
			{
				fprintf(f, "%d, %d, %d,\n", m_Indices[i], m_Indices[i + 1], m_Indices[i + 2]);
				//file << m_Indices[i] << delim << m_Indices[i + 1] << delim << m_Indices[i + 2] << std::endl;
			}
			fprintf(f, "};\n");
			//file << "};" << std::endl;
			fclose(f);
		}

	}

}
