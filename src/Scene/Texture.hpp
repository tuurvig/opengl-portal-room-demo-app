//----------------------------------------------------------------------------------------
/**
 * \file       Texture.hpp
 * \author     Richard Kvasnica
 * \brief      Texture class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <string>

namespace kvasnric
{
	// Abstract texture class wrapping functionality of different texture types
	class Texture
	{
	public:
		// texture types to be assigned to texture slots
		enum TYPE
		{
			DIFFUSE = 0,
			SPECULAR = 1,
			NORMAL = 2,
			ROUGHNESS = 3,
			OCCLUSION = 4,
			OPACITY = 5,
			CUBEMAP = 6
		};

		/**
		 * Texture constructor generates opengl texture object
		 * @param filename texture filename
		 * @param type texture type
		 */
		Texture(const std::string& filename, TYPE type);
		virtual ~Texture();

		/**
		 * Abstract bind method. Needs to be implemented in child classes
		 */
		virtual void Bind() const = 0;

		/**
		 * @returns Texture type of an instance
		 */
		inline unsigned GetType() const { return m_Type; }

		/**
		 * @return Texture name
		 */
		inline std::string GetName() const { return m_Name; }
	protected:
		std::string m_Name;
		unsigned m_ID;
		TYPE m_Type;
	};

	// Child class of a Texture. Constructs single image texture file
	class Texture2D final : public Texture
	{
	public:
		/**
		 * Constructor that loads single texture file based on filename
		 */
		Texture2D(const std::string& filename, TYPE type);
		~Texture2D() override = default;

		/**
		 * Binds basic texture2d target to its texture slot
		 */
		void Bind() const override;
	private:
	};
}