//----------------------------------------------------------------------------------------
/**
 * \file       PortalTextureShader.cpp
 * \author     Richard Kvasnica
 * \brief      Child class portal texture shader definition
*/
//----------------------------------------------------------------------------------------

#include "PortalTextureShader.hpp"

#include <constants.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <gl_core_4_4.h>

namespace kvasnric
{
	PortalTextureShader::PortalTextureShader()
		: ShaderProgram(ReadShaderFromFile("res/shaders/portalTex.vert"), ReadShaderFromFile("res/shaders/portalTex.frag"))
		, u_PV(-1), u_Model(-1), u_Portal(-1), u_Frame(-1), m_Count(0), m_Billboard(nullptr)
	{
		AssignLocation(u_PV);
		AssignLocation(u_Model);
		AssignLocation(u_Portal);
		AssignLocation(u_Frame);

		SetUniform1i(u_Portal, Texture::DIFFUSE);
		
		m_Billboard.reset(new VertexArray());
		InitBillboard();
	}

	void PortalTextureShader::Render(const Portal& portal, float time, const glm::mat4& view, const glm::mat4& projection) const
	{
		// bind this shader
		Bind();

		m_Billboard->Bind();

		// bind portal dynamic texture
		portal.Bind();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		const auto model = portal.GetModelMatrix();

		// dynamic texture was created with 30 frames in mind.
		const int currentFrame = (int)(time * 30);

		SetUniform1i(u_Frame, currentFrame % 10);
		SetUniformMat4(u_Model, model);
		SetUniformMat4(u_PV, projection*view);

		glDrawArrays(GL_TRIANGLES, 0, m_Count);
		glDisable(GL_BLEND);
	}
	
	void PortalTextureShader::InitBillboard()
	{
		// aspect ratio of one frame in the texture
		const float ratio = 660.0f / 970.0f;
		
		float verts[] = {
			-ratio, -1.0f, 0.0f, 0.0f, 0.0f,
			-ratio, 1.0f, 0.0f, 0.0f, 1.0f,
			ratio, 1.0f, 0.0f, 1.0f, 1.0f,

			ratio, 1.0f, 0.0f, 1.0f, 1.0f,
			ratio, -1.0f, 0.0f, 1.0f, 0.0f,
			-ratio, -1.0f, 0.0f, 0.0f, 0.0f
		};

		m_Count = sizeof(verts) / sizeof(float);

		m_Billboard.reset(new VertexArray());
		m_Billboard->Bind();

		m_Billboard->SetVertexBuffer(std::make_unique<VertexBuffer>( verts, sizeof(verts), DRAW::STATIC));

		m_Billboard->EnableVertexAttrib(POSITION_LOC);
		m_Billboard->SetVertexAttribPointer(POSITION_LOC, 0, 5 * sizeof(float));

		m_Billboard->EnableVertexAttrib(TEX_COORD_LOC);
		m_Billboard->SetVertexAttribPointer(TEX_COORD_LOC, 3 * sizeof(float), 5 * sizeof(float));
	}

}
