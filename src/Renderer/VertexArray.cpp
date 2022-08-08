//----------------------------------------------------------------------------------------
/**
 * \file       VertexArray.cpp
 * \author     Richard Kvasnica
 * \brief      Vertex Array definition
 *
 * Class wrapping the functionality of OpenGL vertex array object
*/
//----------------------------------------------------------------------------------------

#include "VertexArray.hpp"

#include <gl_core_4_4.h>

namespace kvasnric
{
	VertexArray::VertexArray()
		: m_ID(0)
	{
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexAttribPointer(unsigned short location, unsigned offset, unsigned stride, bool normalize)
	{
		glVertexAttribPointer(location, 3, GL_FLOAT, normalize, stride, (void*) offset);
	}

	void VertexArray::EnableVertexAttrib(unsigned short location)
	{
		glEnableVertexAttribArray(location);
	}
}
