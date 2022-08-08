//----------------------------------------------------------------------------------------
/**
 * \file       StencilStamp.hpp
 * \author     Richard Kvasnica
 * \brief      Stencil simplifier class declaration
 *
 * Simplifies rendering only to the stencil buffer and sets stencil configurations.
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "ShaderProgram.hpp"
#include <Scene/Model.hpp>

namespace kvasnric
{
	class StencilStamp final : public ShaderProgram
	{
	public:
		StencilStamp();

		/**
		 * Renders vertex data and increases value of the stencil buffer when the stencil value equals to stampId - 1.
		 * @param vao vertex data
		 * @param count number of elements to draw vertices
		 * @param pvm tansform stamp into the world
		 * @param stampId stamp value that will be written into stencil buffer
		 */
		void StampElements(const VertexArray& vao, unsigned count, const glm::mat4& pvm, unsigned stampId) const;

		/**
		 * Always writes a value into stencil buffer. Turns off writing into depth buffer.
		 * @param vao vertex data
		 * @param count number of elements to draw vertices
		 * @param pvm tansform stamp into the world
		 * @param stampId stamp value that will be written into stencil buffer
		 */
		void StampElementsFirst(const VertexArray& vao, unsigned count, const glm::mat4& pvm, unsigned stampId) const;

		/**
		 * Makes a stamp from Model instance.
		 * @param m Model instance
		 * @param pvm tansform stamp into the world
		 * @param stampId stamp value that will be written into stencil buffer
		 */
		void StampModel(const Model& m, const glm::mat4& pvm, unsigned stampId) const;

		/**
		 * reads pixel value from stencil buffer
		 */
		static unsigned ReadStencilPixelValue(int x, int y);

		/**
		 * sets stencil function to write a value when we want other shader to be used.
		 */
		static void StampWithShader(unsigned stampId);

		/**
		 * sets stencil compare function to equal to the value of stampId
		 */
		static void CompareToStamp(unsigned stampId);

		/**
		 * sets stencil compare function to lequal to the value of stampId
		 */
		static void CheckInStamp(unsigned stampId);
		
		static void EnableTest();
		static void DisableTest();

		~StencilStamp() override = default;
	private:
		int u_PVM;
	};
}