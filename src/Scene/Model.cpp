//----------------------------------------------------------------------------------------
/**
 * \file       Model.cpp
 * \author     Richard Kvasnica
 * \brief      Model class declaration
*/
//----------------------------------------------------------------------------------------

#include "Model.hpp"

namespace kvasnric
{
	Mesh& Model::NewMesh()
	{
		m_Meshes.emplace_back(std::make_unique<Mesh>());
		return *m_Meshes.back();
	}
}