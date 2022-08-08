//----------------------------------------------------------------------------------------
/**
 * \file       Mouse.hpp
 * \author     Richard Kvasnica
 * \brief      Static Mouse class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <glm/glm.hpp>

namespace kvasnric
{
	// Static class handling the mouse current state
	class Mouse
	{
	public:
		/**
		 * Sets current position of the mouse
		 */
		static void RegisterPosition(int x, int y);

		/**
		 * Sets original position of the mouse (before movement)
		 */
		static void SetOriginPosition(int x, int y);

		/**
		 * Relative motion of a mouse based on the current position agains the original mouse position
		 * @returns two component vector 
		 */
		static glm::vec2 GetRelativeMotion();

		/**
		 * @returns Coordinates of the current mouse position
		 */
		static glm::i16vec2 GetCoords();

		/**
		 * Registers button press
		 */
		static void SetButtonPressed(int button);

		/**
		 * Registers button release
		 */
		static void SetButtonReleased(int button);

		/**
		 * @returns If right mouse button is active
		 */
		static bool IsRight();

		/**
		 * @returns If left mouse button is active
		 */
		static bool IsLeft();

		/**
		 * @returns If middle mouse button is active
		 */
		static bool IsMiddle();
	private:
		// hardcoded button values
		enum BUTTON
		{
			LEFT = 0,
			MIDDLE = 1,
			RIGHT = 2,
			COUNT = 3
		};

		static glm::i16vec2 s_CurrentPos;
		static glm::i16vec2 s_LastPos;
		static bool s_Pressed[BUTTON::COUNT];
	};
}

