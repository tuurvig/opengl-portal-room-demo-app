//----------------------------------------------------------------------------------------
/**
 * \file       OpenGLApplication.hpp
 * \author     Richard Kvasnica
 * \brief      Abstract OpenGL application
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Window.hpp"
#include <Scene/Resources.hpp>

namespace kvasnric
{
	/**
	 * Abstract class sets functionality for OpenGL Applications build for callback interface
	 * Inherits from Window class
	 */
	class OpenGLApplication : public Window
	{
	public:
		/**
		 * OpenGLApplication constructor takes in three parameters to construct Window
		 * @param width Window width
		 * @param height Window height
		 * @param title Window title
		 */
		OpenGLApplication(int width, int height, const char* title);
		~OpenGLApplication() override = default;
		
		// deleted constructors
		OpenGLApplication(const OpenGLApplication&) = delete;
		OpenGLApplication(const OpenGLApplication&&) = delete;
		OpenGLApplication& operator=(OpenGLApplication&&) = delete;
		OpenGLApplication& operator=(const OpenGLApplication&) = delete;
		
		/**
		 * Sets up first properties of OpenGL
		 */
		virtual void Init();

		/**
		 * Load resources of the application
		 */
		virtual void LoadResources();
		
		/**
		 * Used to setup resources of the application after init and load resources
		 */
		virtual void Setup();

		/**
		 * Abstract Render method, needs to be implemented in child classes.
		 */
		virtual void Render() = 0;

		/**
		 * Resize window callback
		 * @param width window width
		 * @param height window height
		 */
		virtual void ResizeWindow(int width, int height);

		/**
		 * Timer callback used to refresh class properties. Calls TimerUpdate()
		 * @param id timerfunc id
		 * @param time current time in milliseconds 
		 */
		virtual void Timer(int id, int time);

		/**
		 * Called by Timer method. Used to update application properties.
		 */
		virtual void TimerUpdate();
		/**
		 * Implement a reaction to mouse click. Does nothing in abstract.
		 */
		virtual void MouseClick();

		/**
		 * Implement a reaction to a key press. Does nothing in abstract.
		 */
		virtual void ReactOnKey();

		/**
		 * Implement a reaction to special key. Does nothing in abstract.
		 */
		virtual void ReactOnSpecialKey();

		/**
		 * Tells if an application is running
		 * @returns Bool whether the application is running
		 */
		inline bool IsRunning() const { return m_Run; }

		void SetCurrentTime(int time);
	protected:
		/**
		 * Implements a reaction to resize callback. Does nothing in abstract.
		 */
		virtual void ResizeUpdate();

		/**
		 * Sets whether an app should use multisampling
		 * @param option used to enabling/disabling
		 */
		static void SetMultiSampling(bool option);

		/**
		 * Sets rendering base clear color
		 * @param r red component
		 * @param g green component
		 * @param b blue component
		 * @param a alpha component
		 */
		static void SetClearColor(float r, float g, float b, float a);

		/**
		 * Sets whether an app should use depth test
		 * @param option used to enabling/disabling
		 */
		static void SetDepthTest(bool option);
		
		/**
		 * Clears/Resets color, depth and stencil buffer
		 */
		static void Clear();

		/**
		 * Clears/Resets stencil buffer
		 */
		static void ClearStencil();

		/**
		 * Clears/Resets depth buffer
		 */
		static void ClearDepth();

		/**
		 * Does pgr framework call to check gl errors
		 */
		static void CheckErrors();

		/**
		 * Enables culling
		 */
		static void EnableCulling();

		/**
		 * Called by ResizeWindow callback. Does a gl call to update the viewport of a window.
		 */
		void SetViewport(int width, int height);

		Resources m_Res;
		int m_CurrentTimeMs;
		float m_CurrentTime;
		float m_TimeDelta;
		bool m_Run;
	};

}

