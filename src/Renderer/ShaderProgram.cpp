//----------------------------------------------------------------------------------------
/**
 * \file       ShaderProgram.cpp
 * \author     Richard Kvasnica
 * \brief      Shader Program definition
*/
//----------------------------------------------------------------------------------------

#include "ShaderProgram.hpp"
#include "pgr.h"

#include <stdexcept>
#include <sstream>
#include <fstream>

namespace kvasnric
{
	ShaderProgram::ShaderProgram(const std::string& vertexSrc, const std::string& fragSrc)
		: m_ID(0)
		, m_Vert(pgr::createShaderFromSource(GL_VERTEX_SHADER, vertexSrc))
		, m_Frag(pgr::createShaderFromSource(GL_FRAGMENT_SHADER, fragSrc))
	{
		GLuint sh[3] = { m_Vert, m_Frag, 0 };

		m_ID = pgr::createProgram(sh);

		if (m_ID == 0)
			throw std::runtime_error("Failed to create program");

		glUseProgram(m_ID);
	}

	ShaderProgram::~ShaderProgram()
	{
		Unbind();
		pgr::deleteProgramAndShaders(m_ID);
	}

	void ShaderProgram::Bind() const
	{
		glUseProgram(m_ID);
	}

	void ShaderProgram::Unbind()
	{
		glUseProgram(0);
	}

	std::string ShaderProgram::ReadShaderFromFile(const std::string& path)
	{
		const std::ifstream shaderFile(path);

		if (!shaderFile.is_open())
		{
			const std::string msg = "Problem reading shader path on file: " + path;
			throw std::runtime_error( msg.c_str() );
		}

		std::string ret;
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		return shaderStream.str();
	}

	void ShaderProgram::RenderBackFace()
	{
		glCullFace(GL_BACK);
	}

	void ShaderProgram::RenderFrontFace()
	{
		glCullFace(GL_FRONT);
	}

	void ShaderProgram::EnableBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void ShaderProgram::DisableBlending()
	{
		glDisable(GL_BLEND);
	}

	void ShaderProgram::RenderElements(const unsigned offset, const unsigned count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*) offset);
	}
	
	int ShaderProgram::GetAttribLocation(const std::string& name) const
	{
		return glGetAttribLocation(m_ID, name.c_str());
	}

	void ShaderProgram::RegisterUniform(const std::string& name)
	{
		const auto it = m_UniformLocations.find(name);

		if (it == m_UniformLocations.end())
		{
			const auto res = m_UniformLocations.insert(
				{ name, glGetUniformLocation(m_ID, name.c_str()) });
		}
	}

	int ShaderProgram::GetUniformLocation(const char* name) const
	{
		return glGetUniformLocation(m_ID, name);
	}

	inline int ShaderProgram::GetUniformLocation(const std::string& name) const
	{
		return m_UniformLocations.find(name)->second;
	}

	void ShaderProgram::SetUniform1i(const std::string& name, int value) const
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform1i(const int location, int value)
	{
		glUniform1i(location, value);
	}

	void ShaderProgram::SetUniform1f(const std::string& name, float value) const
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform1f(const int location, float value)
	{
		glUniform1f(location, value);
	}

	void ShaderProgram::SetUniform2f(const std::string& name, const glm::vec2& value) const
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void ShaderProgram::SetUniform2f(const int location, const glm::vec2& value)
	{
		glUniform2f(location, value.x, value.y);
	}

	void ShaderProgram::SetUniform3f(const std::string& name, const glm::vec3& value) const
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void ShaderProgram::SetUniform3f(const int location, const glm::vec3& value)
	{
		glUniform3f(location, value.x, value.y, value.z);
	}

	void ShaderProgram::SetUniform4f(const std::string& name, const glm::vec4& value) const
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::SetUniform4f(const int location, const glm::vec4& value)
	{
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::SetUniformMat3(const std::string& name, const glm::mat3& matrix) const
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderProgram::SetUniformMat3(const int location, const glm::mat3& matrix)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderProgram::SetUniformMat4(const int location, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
