//----------------------------------------------------------------------------------------
/**
 * \file       VertexArray.hpp
 * \author     Richard Kvasnica
 * \brief      Vertex Array declaration
 *
 * Class wrapping the functionality of OpenGL vertex array object
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <memory>
#include "Buffer.hpp"

namespace kvasnric
{
	// Class wrapping the functionality of OpenGL vertex array object
	class VertexArray
	{
	public:
		/**
		 * Constructs new vertex array object (VAO)
		 */
		VertexArray();
		~VertexArray();

		/**
		 * Binds VAO to currently binded opengl program
		 */
		void Bind() const;

		/**
		 * Unbinds VAO
		 */
		static void Unbind();

		/**
		 * Assigns vertex buffer object to vao
		 * @param vbo r-value reference to unique pointer of an vbo
		 */
		inline void SetVertexBuffer(std::unique_ptr<VertexBuffer>&& vbo)
		{
			m_VertexBuffer = std::move(vbo);
		}

		/**
		 * Assigns element buffer object to vao
		 * @param ebo r-value reference to unique pointer of an ebo
		 */
		inline void SetElementBuffer(std::unique_ptr<ElementBuffer>&& ebo)
		{
			m_ElementBuffer = std::move(ebo);
		}

		/**
		 * Wraps opengl call of glVertexAttribPointer
		 */
		static void SetVertexAttribPointer(unsigned short location, unsigned offset, unsigned stride, bool normalize = false);

		/**
		 * Wraps opengl call of glEnableVertexAttribArray
		 */
		static void EnableVertexAttrib(unsigned short location);
	private:
		unsigned m_ID;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<ElementBuffer> m_ElementBuffer;
	};
}
