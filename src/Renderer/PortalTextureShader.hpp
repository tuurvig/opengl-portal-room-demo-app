//----------------------------------------------------------------------------------------
/**
 * \file       PortalTextureShader.hpp
 * \author     Richard Kvasnica
 * \brief      Child class portal texture shader declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "ShaderProgram.hpp"

#include <Portal.hpp>

namespace kvasnric
{
	class PortalTextureShader final : public  ShaderProgram
	{
	public:
		PortalTextureShader();
		~PortalTextureShader() override = default;

		/**
		 * Renders one portal in the scene by drawing dynamic texture.
		 * @param portal Portal instance holding dynamic texture inside
		 * @param time Current time used for determining which frames are to be drawn in seconds.
		 * @param view View transformation matrix
		 * @param projection Projection transformation matrix
		 */
		void Render(const Portal& portal, float time, const glm::mat4 & view, const glm::mat4 & projection) const;
	private:
		/**
		 * Function initializes a vao quad with position and texture coordinates.
		 */
		void InitBillboard();
		
		int u_PV;
		int u_Model;
		int u_Portal;
		int u_Frame;
		
		int m_Count;
		 
		std::unique_ptr<VertexArray> m_Billboard;
	};
}