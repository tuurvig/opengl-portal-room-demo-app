//----------------------------------------------------------------------------------------
/**
 * \file       Mouse.cpp
 * \author     Richard Kvasnica
 * \brief      Static Mouse class definition
*/
//----------------------------------------------------------------------------------------

#include "Mouse.hpp"

namespace kvasnric
{
	bool Mouse::s_Pressed[BUTTON::COUNT] = { false };
	glm::i16vec2 Mouse::s_CurrentPos = { 0, 0 };
	glm::i16vec2 Mouse::s_LastPos = { 0, 0 };

	void Mouse::RegisterPosition(int x, int y)
	{
		s_CurrentPos.x = x;
		s_CurrentPos.y = y;
	}

	void Mouse::SetOriginPosition(int x, int y)
	{
		s_LastPos.x = x;
		s_LastPos.y = y;
	}

	glm::vec2 Mouse::GetRelativeMotion()
	{
		// difference between original position and the new position.
		return { s_CurrentPos.x - s_LastPos.x, s_LastPos.y - s_CurrentPos.y };
	}

	glm::i16vec2 Mouse::GetCoords()
	{
		return s_CurrentPos;
	}

	void Mouse::SetButtonPressed(int button)
	{
		s_Pressed[button] = true;
	}

	void Mouse::SetButtonReleased(int button)
	{
		s_Pressed[button] = false;
	}

	bool Mouse::IsLeft()
	{
		return s_Pressed[BUTTON::LEFT];
	}

	bool Mouse::IsMiddle()
	{
		return s_Pressed[BUTTON::MIDDLE];
	}

	bool Mouse::IsRight()
	{
		return s_Pressed[BUTTON::RIGHT];
	}

}