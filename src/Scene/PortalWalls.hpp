//----------------------------------------------------------------------------------------
/**
 * \file       PortalWalls.hpp
 * \author     Richard Kvasnica
 * \brief      Model child class, portal walls declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Model.hpp"
#include "Texture.hpp"

namespace kvasnric
{
	class PortalWalls final : public Model
	{
	public:
		/**
		 * Hardcoded model. 34 faces.
		 * Constructs Portal Walls with different types of material properties 
		 */
		PortalWalls( std::shared_ptr<Texture2D> diffuse, std::shared_ptr<Texture2D> specular, std::shared_ptr<Texture2D> normal, std::shared_ptr<Texture2D> rough, std::shared_ptr<Texture2D> ao );
	private:
		Mesh * m_Mesh;
	};
}
