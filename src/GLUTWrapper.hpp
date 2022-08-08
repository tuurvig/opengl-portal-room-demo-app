//----------------------------------------------------------------------------------------
/**
 * \file       GLUTWrapper.hpp
 * \author     Richard Kvasnica
 * \brief      GLUT Wrapper declaration
 *
 * Static class that neatly packs GLUT functionality
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <OpenGLApplication.hpp>

namespace kvasnric
{
	// Static class that neatly packs GLUT functionality
	class GLUTWrapper
	{
	public:
		/**
		 * Initializes glut, opengl context and sets up an instance of OpenGLApplication
		 * @param argc terminal argument count
		 * @param argv terminal argument values
		 * @param app pointer to existing openglapplication
		 */
		static void Init(int argc, char** argv, OpenGLApplication* app);

		/**
		 * Calls GLUTMainLoop and destroys the application when the loop ends
		 */
		static void Run();

		/**
		 * Terminates with error by calling function of pgr framework to die with error.
		 */
		static void TerminateWithError(const char * err);

		/**
		 * Destroys OpenGLApplication
		 */
		static void Destroy();

		/**
		 * Sets timer refresh time. The interval between timer updates.
		 * @param time time in milliseconds
		 */
		static void SetRefreshTime(int time);
	private:
		
		/**
		 * Calls render function of an OpenGLApplication instance and swaps buffers.
		 */
		static void OnDisplay();

		/**
		 * Handles key press when in interval 10 < key < 97. Doesn't react twice on the same key press.
		 * Registers key press to keyboard class
		 */
		static void OnKey(unsigned char key, int x, int y);

		/**
		 * Handles key up when in interval 10 < key < 97. Registers in keyboard class.
		 */
		static void OnKeyUp(unsigned char key, int x, int y);

		/**
		 * Register special key press value to keyboard class
		 */
		static void OnSpecialKey(int key, int x, int y);

		/**
		 * Register special key up to keyboard class
		 */
		static void OnSpecialKeyUp(int key, int x, int y);

		/**
		 * Callback to handle window change in width and height
		 */
		static void OnReshape(int width, int height);

		/**
		 * Periodical callback that calls timer method of OpenGLApplication.
		 * Checks if an app is still running.
		 * Teleports cursor back to the center of the screen
		 */
		static void OnTimer(int id);

		/**
		 * Registers mouse motion to mouse class.
		 */
		static void OnMouseMotion(int x, int y);

		/**
		 * Does exactly the same as OnMouseMotion
		 */
		static void OnActiveMouseMotion(int x, int y);

		/**
		 * Registers mouse clicks
		 */
		static void OnMouse(int button, int state, int x, int y);

		static void OnWindowFocus(int state);

		/**
		 * Closes the application
		 */
		static void OnClose();

		static OpenGLApplication* s_App;

		static int s_RefreshTimeMs;
		static bool s_Repeat;
		static bool s_WindowActive;
		static int s_CenterX;
		static int s_CenterY;
	};
}
