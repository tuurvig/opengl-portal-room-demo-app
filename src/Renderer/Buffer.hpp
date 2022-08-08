//----------------------------------------------------------------------------------------
/**
 * \file       Buffer.hpp
 * \author     Richard Kvasnica
 * \brief      VBO and EBO class declarations
 *
 * Class wrapping the functionality of OpenGL vertex buffer objects
*/
//----------------------------------------------------------------------------------------

#pragma once

namespace kvasnric
{
	// hardcoded GLenum values
	enum class DRAW
	{
		STATIC = 0x88E4,
		DYNAMIC = 0x88E8,
		STREAM = 0x88E0
	};

	// Class wraps functionality of vertex buffer object (VBO)
	class VertexBuffer
	{
	public:
		/**
		 * Vertex buffer constructor. Creates VBO and pushes the data onto the GPU
		 * @param vertices pointer to the vertex data that will be pushed to the gpu
		 * @param size size of allocated vertex data in bytes
		 * @param type tells how the gpu should store the data
		 */
		VertexBuffer(const void* vertices, unsigned size, DRAW type);
		~VertexBuffer();

		/**
		 * Binds VBO to the current vertex array object (VAO)
		 */
		void Bind() const;

		/**
		 * Unbinds VBO
		 */
		static void Unbind();

		/**
		 * @returns Draw type of this vertex buffer object
		 */
		DRAW DrawType() const { return m_Type; }
	private:
		unsigned m_ID;
		DRAW m_Type;
	};

	// Class wraps functionality of element buffer object (EBO)
	class ElementBuffer
	{
	public:
		/**
		 * Element buffer constructor. Creates EBO and pushes the data onto the GPU
		 * @param indices pointer to data holding vertex indices from a VBO that will be pushed to the gpu
		 * @param size size of allocated indices data in bytes
		 * @param type tells how the gpu should store the data
		 */
		ElementBuffer(const void* indices, unsigned size, DRAW type);
		~ElementBuffer();

		/**
		 * Binds EBO to the current vertex array object (VAO)
		 */
		void Bind() const;

		/**
		 * Unbinds EBO
		 */
		static void Unbind();

		/**
		 * @returns Draw type of this element buffer object
		 */
		DRAW DrawType() const { return m_Type; }
	private:
		unsigned m_ID;
		DRAW m_Type;
	};
}

