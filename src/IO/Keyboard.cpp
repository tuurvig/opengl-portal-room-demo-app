//----------------------------------------------------------------------------------------
/**
 * \file       Keyboard.cpp
 * \author     Richard Kvasnica
 * \brief      Static Keyboard class definition
*/
//----------------------------------------------------------------------------------------

#include "Keyboard.hpp"

namespace kvasnric
{
	bool Keyboard::s_Key[KEY::COUNT] = { false };

	void Keyboard::Press(const int key)
	{
		s_Key[key] = true;
	}

	void Keyboard::Release(const int key)
	{
		s_Key[key] = false;
	}

	bool Keyboard::IsPressed(const int key)
	{
		return s_Key[key];
	}

	bool Keyboard::IsLeftAltPressed()
	{
		return s_Key[KEY::L_ALT];
	}

	bool Keyboard::IsLeftCtrlPressed()
	{
		return s_Key[KEY::L_CTRL];
	}

	bool Keyboard::IsLeftShiftPressed()
	{
		return s_Key[KEY::L_SHIFT];
	}

}
