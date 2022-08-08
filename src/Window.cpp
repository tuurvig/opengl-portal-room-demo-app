//----------------------------------------------------------------------------------------
/**
 * \file       Window.cpp
 * \author     Richard Kvasnica
 * \brief      Window class definition
*/
//----------------------------------------------------------------------------------------

#include "Window.hpp"

namespace kvasnric
{
	Window::Window(int width, int height, const char* title)
		: m_Width(width), m_Height(height), m_Title(title)
	{
	}

	void Window::Update(int width, int height)
	{
		m_Width = width;
		m_Height = height;
	}
}
