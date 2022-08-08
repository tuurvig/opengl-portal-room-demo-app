//----------------------------------------------------------------------------------------
/**
 * \file       Buffer.cpp
 * \author     Richard Kvasnica
 * \brief      VBO and EBO class definitions
*/
//----------------------------------------------------------------------------------------

#include "Buffer.hpp"

#include "gl_core_4_4.h"

namespace kvasnric
{
	/////////////////////////////////////////////
	// VBO
	VertexBuffer::VertexBuffer(const void* vertices, unsigned size, DRAW type)
		: m_ID(0), m_Type(type)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, (GLenum) m_Type);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//////////////////////////////////////////////
	// EBO
	ElementBuffer::ElementBuffer(const void* indices, unsigned size, DRAW type)
		: m_ID(0), m_Type(type)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, (GLenum) m_Type);
	}

	ElementBuffer::~ElementBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void ElementBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void ElementBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}