//----------------------------------------------------------------------------------------
/**
 * \file       StencilStamp.cpp
 * \author     Richard Kvasnica
 * \brief      Stencil simplifier class definition
 *
 * Simplifies rendering only to the stencil buffer and sets stencil configurations.
*/
//----------------------------------------------------------------------------------------

#include "StencilStamp.hpp"

#include <gl_core_4_4.h>

namespace kvasnric
{
	StencilStamp::StencilStamp()
		: ShaderProgram( ReadShaderFromFile("res/shaders/stencilStamp.vert"), ReadShaderFromFile("res/shaders/stencilStamp.frag"))
		, u_PVM(-1)
	{
		Bind();
		
		AssignLocation(u_PVM);
	}

	void StencilStamp::StampElements(const VertexArray& vao, unsigned count, const glm::mat4& pvm, unsigned stampId) const
	{
		// binds shader
		Bind();

		// turns depth buffer to be read only
		glDepthMask(GL_FALSE);

		// enables stencil test
		EnableTest();

		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		glStencilFunc(GL_EQUAL, stampId-1, 0xFF);

		vao.Bind();
		SetUniformMat4(u_PVM, pvm);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

		// enables writing to depth buffer back
		glDepthMask(GL_TRUE);
	}

	void StencilStamp::StampElementsFirst(const VertexArray& vao, unsigned count, const glm::mat4& pvm,
		unsigned stampId) const
	{
		Bind();

		glDepthMask(GL_FALSE);

		EnableTest();

		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, stampId, 0xFF);

		vao.Bind();
		SetUniformMat4(u_PVM, pvm);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

		glDepthMask(GL_TRUE);
	}

	void StencilStamp::StampModel(const Model& m, const glm::mat4& pvm, unsigned stampId) const
	{
		Bind();

		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, stampId, 0xFF);
		SetUniformMat4(u_PVM, pvm);
		
		for (const auto & mesh : m.GetMeshes())
		{
			mesh->Bind();
			glDrawElements(GL_TRIANGLES, mesh->GetCountOfIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}

	unsigned StencilStamp::ReadStencilPixelValue(const int x, const int y)
	{
		unsigned char pixel = 0;
		glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &pixel);
		return pixel;
	}

	void StencilStamp::StampWithShader(unsigned stampId)
	{
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, stampId, 0xFF);
	}

	void StencilStamp::CompareToStamp(unsigned stampId)
	{
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_EQUAL, stampId, 0xFF);
	}

	void StencilStamp::CheckInStamp(unsigned stampId)
	{
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_LEQUAL, stampId, 0xFF);
	}

	void StencilStamp::EnableTest()
	{
		glEnable(GL_STENCIL_TEST);
	}

	void StencilStamp::DisableTest()
	{
		glDisable(GL_STENCIL_TEST);
	}
}
