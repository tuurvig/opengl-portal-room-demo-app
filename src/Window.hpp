//----------------------------------------------------------------------------------------
/**
 * \file       Window.hpp
 * \author     Richard Kvasnica
 * \brief      Window class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <string>

namespace kvasnric
{
	// Window class that holds its width, height and title
	class Window
	{
	public:
		/**
		 * Window constructor
		 */
		Window(int width, int height, const char* title);
		virtual ~Window() = default;

		/**
		 * Updates both width and height on the window instance
		 * @param width new width
		 * @param height new height
		 */
		void Update(int width, int height);

		/**
		 * Updates title of the window instance
		 * @param newTitle new title
		 */
		inline void UpdateTitle(const std::string& newTitle) { m_Title = newTitle; }

		/**
		 * @returns Width of the window instance
		 */
		inline int Width() const { return m_Width; }

		/**
		 * @returns Height of the window instance
		 */
		inline int Height() const { return m_Height; }

		/**
		 * @returns Title of the window instance
		 */
		inline const std::string& Title() const { return m_Title; }
	private:
		int m_Width;
		int m_Height;
		std::string m_Title;
	};
}
