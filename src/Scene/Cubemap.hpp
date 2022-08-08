//----------------------------------------------------------------------------------------
/**
 * \file       Cubemap.hpp
 * \author     Richard Kvasnica
 * \brief      Cubemap texture and shader class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Texture.hpp"
#include <Renderer/ShaderProgram.hpp>

namespace kvasnric
{
	// Child texture class that wraps functionality and loading of cubemap texture
	class CubeMap final : public Texture
	{
	public:
		/**
		 * Constructor loads six images to create cubemap by filename
		 */
		CubeMap(const std::string& filename);
		~CubeMap() override = default;

		/**
		 * Binds the cubemap target into its texture slot
		 */
		void Bind() const override;
	private:
	};

	// Child shader program to draw cubemap onto the scene
	class CubeMapShader final : public ShaderProgram
	{
	public:
		/**
		 * Cubemap shader constructor. Compiles glsl source code and sets-up uniforms
		 */
		CubeMapShader();
		~CubeMapShader() override = default;

		/**
		 * Renders cubemap
		 * @param cubemap const reference to a cubemap texture
		 * @param view 4x4 camera matrix
		 * @param projection 4x4 projection matrix
		 */
		void Render( const CubeMap& cubemap, const glm::mat4& view, const glm::mat4& projection ) const;
	private:
		/**
		 * Initializes hardcoded cube vertex data into vao.
		 */
		void InitCube();
		
		int u_PV;
		int u_Cubemap;

		int m_Count;
		std::unique_ptr<VertexArray> m_Cube;
	};
}
