//----------------------------------------------------------------------------------------
/**
 * \file       Model.hpp
 * \author     Richard Kvasnica
 * \brief      Model class declaration
 *
 * Class holds multiple meshes
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
#include "Mesh.hpp"

namespace kvasnric
{
	class Model
	{
	public:
		Model() = default;

		/**
		 * @returns reference to all models meshes.
		 */
		inline const std::vector<std::unique_ptr<Mesh>>& GetMeshes() const { return m_Meshes; }
		inline const std::string& GetDirectory() const { return m_Directory; }

		inline void SetDirectory(std::string&& dir) { m_Directory = std::move(dir); }

		/**
		 * Adds one mesh into the vector of meshes.
		 */
		inline void AddMesh(Mesh&& m) { m_Meshes.emplace_back(std::make_unique<Mesh>(std::move(m))); }
		Mesh& NewMesh();
	protected:
		std::vector<std::unique_ptr<Mesh>> m_Meshes;
		std::string m_Directory;
	};
}
