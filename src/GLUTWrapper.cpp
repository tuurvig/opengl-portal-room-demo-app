//----------------------------------------------------------------------------------------
/**
 * \file       GLUTWrapper.cpp
 * \author     Richard Kvasnica
 * \brief      GLUT Wrapper definition
 *
 * Static class that neatly packs GLUT functionality
*/
//----------------------------------------------------------------------------------------

#include "GLUTWrapper.hpp"

#include <pgr.h>
#include <IO/Keyboard.hpp>
#include <IO/Mouse.hpp>

#include <iostream>

namespace kvasnric
{

#define ASCII_a 97
#define ASCII_OFFSET 32
#define ASCII_RESERVE 10

	// Inits static class members of glut wrapper
	OpenGLApplication* GLUTWrapper::s_App = nullptr;
	int GLUTWrapper::s_RefreshTimeMs = 33;
	bool GLUTWrapper::s_WindowActive = false;
	bool GLUTWrapper::s_Repeat = true;
	int GLUTWrapper::s_CenterX = 0;
	int GLUTWrapper::s_CenterY = 0;

	/** required opengl version - major number */
	const int OGL_VER_MAJOR = 3;
	//required opengl version - minor number
	const int OGL_VER_MINOR = 1;


	void GLUTWrapper::Init(int argc, char** argv, OpenGLApplication* app)
	{
		if (!app)
			throw std::runtime_error("Cannot initialize context with nonexistent application.");

		s_App = app;

		glutInit(&argc, argv);
		glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
		glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
		glutInitWindowSize(s_App->Width(), s_App->Height());

		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

		glutCreateWindow(s_App->Title().c_str());

		if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
			throw std::runtime_error("pgr init failed, required OpenGL not supported?");

		s_App->Init();
		s_App->LoadResources();
		s_App->Setup();

		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		glutFullScreenToggle();

		s_CenterX = s_App->Width() >> 1; s_CenterY = s_App->Height() >> 1;

		// Move cursor on the center of the screen
		glutWarpPointer(s_CenterX, s_CenterY);
		Mouse::SetOriginPosition(s_CenterX, s_CenterY);

		s_App->SetCurrentTime(glutGet(GLUT_ELAPSED_TIME));
		// Assign all callbacks to glut 
		glutDisplayFunc(GLUTWrapper::OnDisplay);
		glutReshapeFunc(GLUTWrapper::OnReshape);
		glutKeyboardFunc(GLUTWrapper::OnKey);
		glutKeyboardUpFunc(GLUTWrapper::OnKeyUp);
		glutSpecialFunc(GLUTWrapper::OnSpecialKey);
		glutSpecialUpFunc(GLUTWrapper::OnSpecialKeyUp);
		glutTimerFunc(s_RefreshTimeMs, GLUTWrapper::OnTimer, 0);
		glutMotionFunc(GLUTWrapper::OnActiveMouseMotion);
		glutMouseFunc(GLUTWrapper::OnMouse);
		glutPassiveMotionFunc(GLUTWrapper::OnMouseMotion);
		glutCloseFunc(GLUTWrapper::OnClose);
		glutEntryFunc(GLUTWrapper::OnWindowFocus);
	}

	void GLUTWrapper::Run()
	{
		glutMainLoop();
		Destroy();
	}


	void GLUTWrapper::Destroy()
	{
		delete s_App;
	}

	void GLUTWrapper::SetRefreshTime(int time)
	{
		s_RefreshTimeMs = time;
	}


	void GLUTWrapper::TerminateWithError(const char* err)
	{
		CHECK_GL_ERROR();
		Destroy();
		pgr::dieWithError(err);
	}

	void GLUTWrapper::OnDisplay()
	{
		s_App->Render();
		glutSwapBuffers();
	}

	void GLUTWrapper::OnKey(unsigned char key, int x, int y)
	{
		// Convert all lowercase characters to uppercase
		key = key >= ASCII_a ? key - ASCII_OFFSET : key;

		// Handles key press when in interval 10 < key < 97. Doesn't react twice on the same key press
		if (key < ASCII_a && key > ASCII_RESERVE && !Keyboard::IsPressed(key))
		{
			Keyboard::Press(key);
			s_App->ReactOnKey();
		}
	}

	void GLUTWrapper::OnKeyUp(unsigned char key, int x, int y)
	{
		// Convert all lowercase characters to uppercase
		key = key >= ASCII_a ? key - ASCII_OFFSET : key;

		if (key < ASCII_a && key > ASCII_RESERVE)
		{
			Keyboard::Release(key);
		}
	}

	void GLUTWrapper::OnSpecialKey(int key, int x, int y)
	{
		if (key < Keyboard::KEY::COUNT && !Keyboard::IsPressed(key))
		{
			Keyboard::Press(key);
			if (key < ASCII_RESERVE) s_App->ReactOnSpecialKey();
		}
	}

	void GLUTWrapper::OnSpecialKeyUp(int key, int x, int y)
	{
		if (key < Keyboard::KEY::COUNT)
		{
			Keyboard::Release(key);
		}
	}

	void GLUTWrapper::OnTimer(int id)
	{
		// if the window is not closing and app is supposed to run 
		if (s_Repeat && s_App->IsRunning())
		{
			// if my cursor is not focus on games window
			if( s_WindowActive )
			{
				// get glut time and update the apps timer
				const int time = glutGet(GLUT_ELAPSED_TIME);
				s_App->Timer(id, time);
				glutPostRedisplay();
				glutWarpPointer(s_CenterX, s_CenterY);
				glutSetCursor(GLUT_CURSOR_CROSSHAIR);
			}
			
			glutTimerFunc(s_RefreshTimeMs, GLUTWrapper::OnTimer, ++id);
		}
		else
		{
			glutLeaveMainLoop();
		}
	}

	void GLUTWrapper::OnReshape(int width, int height)
	{
		// reshape window nad change cursors initial location to the middle of the screen
		s_App->ResizeWindow(width, height);
		s_CenterX = s_App->Width() >> 1;
		s_CenterY = s_App->Height() >> 1;
		Mouse::SetOriginPosition(s_CenterX, s_CenterY);
		glutWarpPointer(s_CenterX, s_CenterY);
	}

	void GLUTWrapper::OnMouse(int button, int state, int x, int y)
	{
		if (button <= 2)
		{
			state ? Mouse::SetButtonReleased(button) : Mouse::SetButtonPressed(button);

			s_App->MouseClick();
		}
	}

	void GLUTWrapper::OnActiveMouseMotion(int x, int y)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
		Mouse::RegisterPosition(x, y);
	}

	void GLUTWrapper::OnMouseMotion(int x, int y)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
		Mouse::RegisterPosition(x, y);
	}

	void GLUTWrapper::OnClose()
	{
		// if the window is about the close cancel the timer
		s_Repeat = false;
	}

	void GLUTWrapper::OnWindowFocus(int state)
	{
		// set window state and warp cursor to the middle of the screen
		s_WindowActive = state;
		glutWarpPointer(s_CenterX, s_CenterY);
		Mouse::SetOriginPosition(s_CenterX, s_CenterY);
		s_App->SetCurrentTime(glutGet(GLUT_ELAPSED_TIME));
	}

}