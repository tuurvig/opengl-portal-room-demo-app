//----------------------------------------------------------------------------------------
/**
 * \file       ShaderProgram.hpp
 * \author     Richard Kvasnica
 * \brief      Shader Program declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

#include <Renderer/VertexArray.hpp>

namespace kvasnric
{
	// Class wrapping functionality of common shader program
	class ShaderProgram
	{
	public:
		/**
		 * Constructs a new shader program by compiling two inputting source strings
		 * @param vertexSrc glsl source code string of vertex shader
		 * @param fragSrc glsl source code string of fragment shader
		 */
		ShaderProgram(const std::string& vertexSrc, const std::string& fragSrc);

		// deletes possible copy/move constructors
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&) = delete;

		/**
		 * virtual destructor that destroys allocated shader program 
		 */
		virtual ~ShaderProgram();

		/**
		 * Binds program to be used in current opengl context
		 */
		void Bind() const;

		/**
		 * Unbinds program
		 */
		static void Unbind();

		/**
		 * Binds location of a custom uniform name to unordered_map (used only in demo testing before)
		 * @param name uniform name in glsl shader
		 */
		void RegisterUniform(const std::string& name);

		/**
		 * Finds program uniform location by name searching the unordered map and assigns to it a integer value
		 */
		void SetUniform1i(const std::string& name, int value) const;

		/**
		 * Finds program uniform location by name searching the unordered map and assigns to it a float value
		 */
		void SetUniform1f(const std::string& name, float value) const;

		/**
		 * Finds program uniform location by name searching the unordered map and assigns to it a two component vector
		 */
		void SetUniform2f(const std::string& name, const glm::vec2& value) const;

		/**
		 * Finds program uniform location by name searching the unordered map and assigns to it a three component vector
		 */
		void SetUniform3f(const std::string& name, const glm::vec3& value) const;

		/**
		 * Finds program uniform location by name searching the unordered map and assigns to it a four component vector
		 */
		void SetUniform4f(const std::string& name, const glm::vec4& value) const;

		/**
		 * Finds program uniform location by name searching the unordered map and assigns to it a 3x3 matrix
		 */
		void SetUniformMat3(const std::string& name, const glm::mat3& matrix) const;

		/**
		 * Finds program uniform location by name searching the unordered map and assigns to it a 4x4 matrix
		 */
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix) const;

		/**
		 * Creates shader glsl source code string by inputting a path to the source
		 * @param path path to the source glsl file
		 */
		static std::string ReadShaderFromFile(const std::string& path);

	protected:
		/**
		 * \def #AssignLocation( var )
		 * \brief Macro that automizes location assignment by stringifying variable name in compile time.
		 * \param var variable to be stringified and later assigned uniform location
		 * Uses static class method GetUniformLocation
		 */
#define AssignLocation( var ) var = GetUniformLocation( #var )

		/**
		 * Does the same as the above, only it takes hard uniform location and assigns value to it in the shader.
		 */
		static void SetUniform1i(int location, int value);
		static void SetUniform1f(int location, float value);
		static void SetUniform2f(int location, const glm::vec2& value);
		static void SetUniform3f(int location, const glm::vec3& value);
		static void SetUniform4f(int location, const glm::vec4& value);
		static void SetUniformMat3(int location, const glm::mat3& matrix);
		static void SetUniformMat4(int location, const glm::mat4& matrix);

		/**
		 * Wraps glDrawElements opengl function
		 */
		static void RenderElements(unsigned offset, unsigned count);

		static void RenderBackFace();
		static void RenderFrontFace();
		static void EnableBlending();
		static void DisableBlending();
		
		/**
		 * @param name vertex attribute name
		 * @returns vertex attribute location 
		 */
		int GetAttribLocation(const std::string& name) const;

		/**
		 * Searches unordered map m_UniformLocations to retreive uniform location
		 * @param name uniform name
		 * @returns location of the uniform
		 */
		int GetUniformLocation(const std::string& name) const;

		/**
		 * Basic wrap of glGetUniformLocation
		 * @name uniform name
		 * @returns location of the uniform
		 */
		int GetUniformLocation(const char* name) const;

		unsigned m_ID;
		unsigned m_Vert;
		unsigned m_Frag;

		std::unordered_map<std::string, int> m_UniformLocations;
	};
}

