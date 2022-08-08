//----------------------------------------------------------------------------------------
/**
 * \file       Keyboard.hpp
 * \author     Richard Kvasnica
 * \brief      Static Keyboard class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

namespace kvasnric
{
	// Static class handling the current state of a keyboard
	class Keyboard
	{
	public:
		// hardcoded Keyboard character ascii values
		enum KEY
		{
			COUNT = 255,
			ESC = 27,
			SPACE = 32,
			ENTER = 13,

			L_SHIFT = 112,
			R_SHIFT = 113,
			L_CTRL = 114,
			R_CTRL = 115,
			L_ALT = 116,
			R_ALT = 117,

			NUM_0 = 48,
			NUM_1 = 49,
			NUM_2 = 50,
			NUM_3 = 51,
			NUM_4 = 52,
			NUM_5 = 53,
			NUM_6 = 54,
			NUM_7 = 55,
			NUM_8 = 56,
			NUM_9 = 57,

			F1 = 1,
			F2 = 2,
			F3 = 3,
			F4 = 4,
			F5 = 5,
			F6 = 6,
			F7 = 7,
			F8 = 8,

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90
		};

		/**
		 * Registers key press
		 */
		static void Press(int key);

		/**
		 * Registers key release
		 */
		static void Release(int key);

		/**
		 * @returns If the key is active
		 */
		static bool IsPressed(int key);

		/**
		 * @returns If the left alt is active
		 */
		static bool IsLeftAltPressed();

		/**
		 * @returns If the left shift is active
		 */
		static bool IsLeftShiftPressed();

		/**
		 * @returns If the left ctrl is active
		 */
		static bool IsLeftCtrlPressed();
	private:
		static bool s_Key[KEY::COUNT];
	};
}
