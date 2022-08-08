//----------------------------------------------------------------------------------------
/**
 * \file       Texture.cpp
 * \author     Richard Kvasnica
 * \brief      Texture class definition
*/
//----------------------------------------------------------------------------------------

#include "Texture.hpp"

#include <pgr.h>
#include <stdexcept>

namespace kvasnric
{
	Texture::Texture(const std::string& filename, TYPE type)
		: m_Name(filename), m_ID(0), m_Type(type)
	{
		glActiveTexture(GL_TEXTURE0 + m_Type);
		glGenTextures(1, &m_ID);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}

	Texture2D::Texture2D(const std::string& filename, TYPE type)
		: Texture(filename, type)
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);

		// loads texture on texture2d target from path
		if (!pgr::loadTexImage2D("res/textures/" + m_Name, GL_TEXTURE_2D))
		{
			const std::string msg = "Cannot load texture: " + m_Name;
			throw std::runtime_error(msg.c_str());
		}

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture2D::Bind() const
	{
		glActiveTexture(GL_TEXTURE0 + m_Type);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}


	
}
