//----------------------------------------------------------------------------------------
/**
 * \file       Cubemap.cpp
 * \author     Richard Kvasnica
 * \brief      Cubemap texture and shader class definition
*/
//----------------------------------------------------------------------------------------

#include "Cubemap.hpp"

#include <pgr.h>
#include <constants.hpp>

namespace kvasnric
{
	CubeMap::CubeMap(const std::string& filename)
		: Texture(filename, CUBEMAP)
	{
		glActiveTexture(GL_TEXTURE0 + m_Type);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);

		// loads six different textures
		const std::string path = "res/textures/cubemaps/" + m_Name;
		if (
			!pgr::loadTexImage2D(path + "_px.png", GL_TEXTURE_CUBE_MAP_POSITIVE_X) ||
			!pgr::loadTexImage2D(path + "_nx.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_X) ||
			!pgr::loadTexImage2D(path + "_py.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Y) ||
			!pgr::loadTexImage2D(path + "_ny.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y) ||
			!pgr::loadTexImage2D(path + "_pz.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Z) ||
			!pgr::loadTexImage2D(path + "_nz.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z))
		{
			const std::string msg = "Cannot load cube map texture: " + m_Name;
			throw std::runtime_error(msg.c_str());
		}

		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	void CubeMap::Bind() const
	{
		glActiveTexture(GL_TEXTURE0 + m_Type);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	}

	CubeMapShader::CubeMapShader()
		: ShaderProgram(ReadShaderFromFile("res/shaders/cubemap.vert"), ReadShaderFromFile("res/shaders/cubemap.frag"))
		, u_PV(-1), u_Cubemap(-1), m_Count( 0 ), m_Cube(nullptr)
	{
		AssignLocation(u_PV);
		AssignLocation(u_Cubemap);

		SetUniform1i(u_Cubemap, Texture::CUBEMAP);
		m_Cube.reset(new VertexArray());
		InitCube();
		Unbind();
	}

	void CubeMapShader::Render(const CubeMap& cubemap, const glm::mat4& view, const glm::mat4& projection) const
	{
		// binds cubemap shader program
		Bind();
		
		// changes depth eval function to less or equal.
		glDepthFunc(GL_LEQUAL);

		// bind cube vao
		m_Cube->Bind();

		// bind cubemap texture
		cubemap.Bind();

		// make a view matrix copy
		glm::mat4 viewT = view;

		// remove translation from the matrix
		viewT[3][0] = 0.0f; viewT[3][1] = 0.0f; viewT[3][2] = 0.0f; viewT[3][3] = 1.0f;

		// upload matrices to the shader as uniforms
		SetUniformMat4(u_PV, projection*viewT);

		// draw triangles of currently bound vao
		glDrawArrays(GL_TRIANGLES, 0, m_Count);

		// switch depth eval function back to less
		glDepthFunc(GL_LESS);
	}

	void CubeMapShader::InitCube()
	{
		// cube vertices definition. Defined in clock-wise order for viewing the cube from the inside while having turned on front culling
		float verts[] = {

			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
 
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,

			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,

			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,

			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f
		};
		
		m_Count = sizeof(verts) / sizeof(float);

		// bind cube vao
		m_Cube->Bind();
		
		// bind a new vertex buffer into this vao
		m_Cube->SetVertexBuffer(std::make_unique<VertexBuffer>(verts, sizeof(verts), DRAW::STATIC));

		// enable and set position vertex attribute
		m_Cube->EnableVertexAttrib(POSITION_LOC);
		m_Cube->SetVertexAttribPointer(POSITION_LOC, 0, 3*sizeof(float));
	}

}
