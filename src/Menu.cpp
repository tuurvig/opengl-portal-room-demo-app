//----------------------------------------------------------------------------------------
/**
 * \file       Menu.cpp
 * \author     Richard Kvasnica
 * \brief      Menu class definition
*/
//----------------------------------------------------------------------------------------

#include "Menu.hpp"

#include <constants.hpp>
#include <gl_core_4_4.h>
#include <Scene/Texture.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace kvasnric
{
	Menu::Menu(std::shared_ptr<Texture2D> background, std::shared_ptr<Texture2D> cursor, const int width, const int height)
		: ShaderProgram(ReadShaderFromFile("res/shaders/menu.vert"), ReadShaderFromFile("res/shaders/menu.frag"))
		, m_Billboard(nullptr), m_Background(std::move(background)), m_Cursor(std::move(cursor)), m_Count(0), m_Ratio((float)(width) / (float)(height))
		, m_Width((float)width), m_Height((float)height), m_Active(false), m_CursorLocation(width / 2, height / 2)
	{
		AssignLocation(u_BG);
		AssignLocation(u_Cursor);
		AssignLocation(u_CursorMatrix);
		
		SetUniform1i(u_BG, Texture2D::DIFFUSE);
		SetUniform1i(u_Cursor, Texture2D::SPECULAR);

		InitBillboard();
	}

	void Menu::Render() const
	{
		// bind menu shader
		Bind();

		// bind backgound texture
		m_Background->Bind();

		// bind cursor texture
		m_Cursor->Bind();

		// bind vao
		m_Billboard->Bind();
		
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SetUniformMat3(u_CursorMatrix, m_CursorMatrix);
		glDrawArrays(GL_TRIANGLES, 0, m_Count);
		
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	void Menu::UpdateCursor(const glm::vec2& motion)
	{	
		m_CursorLocation = m_CursorLocation + motion;
		
		// update position of the cursor and clamp it inside a window
		m_CursorLocation.x = m_CursorLocation.x < 0.0f ? 0.0f : m_CursorLocation.x >= m_Width ? m_Width : m_CursorLocation.x;
		m_CursorLocation.y = m_CursorLocation.y < 0.0f ? 0.0f : m_CursorLocation.y >= m_Height ? m_Height : m_CursorLocation.y;	

		// cursor is 1/20th of the window
		const float scale = 20.0f;

		// scale, translation matrix. Scaling texture coordines up results in scaling the cursor down.
		// ratio correction applied to x axis of texture coordinates
		// translated in the opposite direction so the cursor goes in the right direction
		m_CursorMatrix = {
			m_Ratio * scale, 0.0f, 0.0f,
			0.0f, scale, 0.0f,
			(-m_CursorLocation.x / m_Width)*scale * m_Ratio, ((m_CursorLocation.y / m_Height) - 1)*scale, 1.0f
		};
	}

	void Menu::Resize(const int width, const int height)
	{
		m_Width = (float)width;
		m_Height = (float)height;
		m_Ratio = m_Width / m_Height;
	}

	Menu::BUTTON Menu::Click() const
	{
		const int quitGame = 218;
		const int exitMenu = 314;
		const int wheatley = 502;
		const int static1 = 598;
		const int static2 = 698;
		const int fog = 790;
		const int buttonH = 46;
		
		if (m_CursorLocation.x >= 1094 && m_CursorLocation.x <= 1746 && m_CursorLocation.y <= 838 && m_CursorLocation.y >= quitGame)
		{
			if (m_CursorLocation.y >= quitGame && m_CursorLocation.y <= quitGame + buttonH ) return QUIT_GAME;
			if (m_CursorLocation.y >= exitMenu && m_CursorLocation.y <= exitMenu + buttonH ) return EXIT_MENU;
			if (m_CursorLocation.y >= wheatley && m_CursorLocation.y <= wheatley + buttonH ) return WHEATLEY;
			if (m_CursorLocation.y >= static1 && m_CursorLocation.y <= static1 + buttonH ) return STATIC_1;
			if (m_CursorLocation.y >= static2 && m_CursorLocation.y <= static2 + buttonH ) return STATIC_2;
			if (m_CursorLocation.y >= fog && m_CursorLocation.y <= fog + buttonH ) return TOGGLE_FOG;
			return DEFAULT;
		}
		else return DEFAULT;
	}

	void Menu::InitBillboard()
	{
		const float verts[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f
		};

		m_Count = sizeof(verts) / sizeof(float);

		m_Billboard.reset(new VertexArray());
		
		m_Billboard->Bind();
		m_Billboard->SetVertexBuffer(std::make_unique<VertexBuffer>(verts, sizeof(verts), DRAW::STATIC));

		m_Billboard->EnableVertexAttrib(POSITION_LOC);
		m_Billboard->SetVertexAttribPointer(POSITION_LOC, 0, 5 * sizeof(float));

		m_Billboard->EnableVertexAttrib(TEX_COORD_LOC);
		m_Billboard->SetVertexAttribPointer(TEX_COORD_LOC, 3 * sizeof(float), 5 * sizeof(float));
	}
}
