//----------------------------------------------------------------------------------------
/**
 * \file       Material.hpp
 * \author     Richard Kvasnica
 * \brief      Material class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Texture.hpp"

namespace kvasnric
{
	/**
	 * Class holds every material property. Even mathematical properties and properties defined by texture.
	 * Is able to represent 6 different types of material properties by texture.
	 */
	class Material
	{
	public:
		// Implicit constructur.
		Material();
		// Explicit constructor with mathematical properties.
		Material(const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& ambient, float shininess);

		// Binds active textures to the shader in their rightful slot.
		void Bind() const;

		// setters of mathematical material properties
		void SetDiffuse(const glm::vec3& diffuse);
		void SetSpecular(const glm::vec3& specular);
		void SetAmbient(const glm::vec3& ambient);
		void SetShininess(float shininess);

		// setters of material textures. If the setting texture is not nullptr then it will be added as an active texture.
		void SetDiffuse(std::shared_ptr<Texture2D> diffuse);
		void SetSpecular(std::shared_ptr<Texture2D> specular);
		void SetNormal(std::shared_ptr<Texture2D> normal);
		void SetRoughness(std::shared_ptr<Texture2D> roughness);
		void SetOcclusion(std::shared_ptr<Texture2D> occlusion);
		void SetOpacity(std::shared_ptr<Texture2D> opacity);

		// getters of mathematical material properties
		inline const glm::vec3& GetDiffuse() const { return m_Diffuse; }
		inline const glm::vec3& GetSpecular() const { return m_Specular; }
		inline const glm::vec3& GetAmbient() const { return m_Ambient; }
		inline float GetShininess() const { return m_Shininess; }

		// getters of material textures
		inline std::shared_ptr<Texture2D> GetDiffuseTexture() const { return m_DiffuseT; }
		inline std::shared_ptr<Texture2D> GetSpecularTexture() const { return m_SpecularT; }
		inline std::shared_ptr<Texture2D> GetNormalTexture() const { return m_NormalT; }
		inline std::shared_ptr<Texture2D> GetGlossyTexture() const { return m_RoughnessT; }
		inline std::shared_ptr<Texture2D> GetOcclusionTexture() const { return m_OcclusionT; }
		inline std::shared_ptr<Texture2D> GetOpacityTexture() const { return m_OpacityT; }

		// bools whether the texture is active
		inline bool IsDiffuseTextureActive() const { return m_DiffuseT != nullptr; }
		inline bool IsSpecularTextureActive() const { return m_SpecularT != nullptr; }
		inline bool IsNormalTextureActive() const { return m_NormalT != nullptr; }
		inline bool IsGlossyTextureActive() const { return m_RoughnessT != nullptr; }
		inline bool IsOcclusionTextureActive() const { return m_OcclusionT != nullptr; }
		inline bool IsOpacityTextureActive() const { return m_OpacityT != nullptr; }
	private:
		/**
		 * Detaches texture from a vector of active textures
		 */
		void DetachActiveTexture(std::shared_ptr<Texture2D>& texture);

		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
		glm::vec3 m_Ambient;
		float m_Shininess;

		std::shared_ptr<Texture2D> m_DiffuseT;
		std::shared_ptr<Texture2D> m_SpecularT;
		std::shared_ptr<Texture2D> m_NormalT;
		std::shared_ptr<Texture2D> m_RoughnessT;
		std::shared_ptr<Texture2D> m_OcclusionT;
		std::shared_ptr<Texture2D> m_OpacityT;

		std::vector<std::shared_ptr<Texture2D>> m_ActiveTextures;
	};
}