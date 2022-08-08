//----------------------------------------------------------------------------------------
/**
 * \file       OpenGLApplication.cpp
 * \author     Richard Kvasnica
 * \brief      OpenGL application definition
 *
 * Defines static and default virtual methods for abstract OpenGL Application
*/
//----------------------------------------------------------------------------------------

#include "OpenGLApplication.hpp"

#include "pgr.h"

namespace kvasnric
{
	OpenGLApplication::OpenGLApplication(int width, int height, const char* title)
		: Window(width, height, title), m_CurrentTimeMs(0), m_CurrentTime(0)
		, m_TimeDelta(0), m_Run( true )
	{
	}

	void OpenGLApplication::Init()
	{
		EnableCulling();
		SetDepthTest(true);
		SetMultiSampling(true);
		SetClearColor(0.5f, 0.4f, 0.8f, 1.0f);
		CheckErrors();
	}

	void OpenGLApplication::SetMultiSampling(bool option)
	{
		option ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
	}

	void OpenGLApplication::SetDepthTest(bool option)
	{
		option ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void OpenGLApplication::SetClearColor(const float r, const float g, const float b, const float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLApplication::EnableCulling()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
	}

	void OpenGLApplication::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLApplication::ClearStencil()
	{
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLApplication::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLApplication::SetViewport(int width, int height)
	{
		glViewport(0, 0, width, height);
		Update(width, height);
	}

	void OpenGLApplication::ResizeWindow(int width, int height)
	{
		SetViewport(width, height);
		ResizeUpdate();
	}

	void OpenGLApplication::Timer(int id, int time)
	{
		const float tmp = (float) time / 1000.0f;
		m_TimeDelta = tmp - m_CurrentTime;
		m_CurrentTime = tmp;
		m_CurrentTimeMs = time;
		
		TimerUpdate();
	}

	void OpenGLApplication::SetCurrentTime(int time)
	{
		m_CurrentTime = (float)time / 1000.0f;
		m_CurrentTimeMs = time;
	}
	
	void OpenGLApplication::ReactOnKey()
	{
	}

	void OpenGLApplication::ReactOnSpecialKey()
	{
	}

	void OpenGLApplication::TimerUpdate()
	{
	}

	void OpenGLApplication::ResizeUpdate()
	{
	}

	void OpenGLApplication::MouseClick()
	{
	}

	void OpenGLApplication::LoadResources()
	{
	}

	void OpenGLApplication::CheckErrors()
	{
		CHECK_GL_ERROR();
	}

	void OpenGLApplication::Setup()
	{
	}

}