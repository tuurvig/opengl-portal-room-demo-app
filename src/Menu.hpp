//----------------------------------------------------------------------------------------
/**
 * \file       Menu.hpp
 * \author     Richard Kvasnica
 * \brief      Menu class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <Renderer/ShaderProgram.hpp>
#include <Scene/Texture.hpp>

namespace kvasnric
{
	class Menu final : public ShaderProgram
	{
	public:
		// defines click values of the menu
		enum BUTTON
		{
			TOGGLE_FOG,
			STATIC_1,
			STATIC_2,
			WHEATLEY,
			EXIT_MENU,
			QUIT_GAME,
			DEFAULT
		};

		/**
		 * Creates a menu with a background and a cursor.
		 */
		Menu(std::shared_ptr<Texture2D> background, std::shared_ptr<Texture2D> cursor, int width, int height);
		~Menu() override = default;

		/**
		 * Render overlays the currently rendering scene with menu. Cursor acts like a texture not a single object rendered by a quad.
		 */
		void Render() const;

		/**
		 * Updates cursor position by relative motion
		 */
		void UpdateCursor(const glm::vec2& motion);

		/**
		 * Resizes window.
		 */
		void Resize(int width, int height);

		/**
		 * Handles click action;
		 * @returns current click action
		 */
		BUTTON Click() const;

		/**
		 * @returns whether the menu is active
		 */
		inline bool IsActive() const { return m_Active; }
		inline void ToggleActive() { m_Active = !m_Active; }
	private:
		/**
		 * Initializes VAO of the quad that will be overlaying entire screen
		 */
		void InitBillboard();
		int u_BG;
		int u_Cursor;
		int u_CursorMatrix;
		
		std::shared_ptr<VertexArray> m_Billboard;
		std::shared_ptr<Texture2D> m_Background;
		std::shared_ptr<Texture2D> m_Cursor;
		
		unsigned m_Count;
		float m_Ratio;
		float m_Width;
		float m_Height;

		bool m_Active;
		
		glm::vec2 m_CursorLocation;
		glm::mat3 m_CursorMatrix;
	};
}