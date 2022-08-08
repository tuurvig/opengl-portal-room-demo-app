//----------------------------------------------------------------------------------------
/**
 * \file       Material.cpp
 * \author     Richard Kvasnica
 * \brief      Material class definition
*/
//----------------------------------------------------------------------------------------

#include "Material.hpp"

namespace kvasnric
{
	Material::Material()
		: m_Diffuse(0), m_Specular(0), m_Ambient(0), m_Shininess(0.0f)
		, m_DiffuseT(nullptr), m_SpecularT(nullptr), m_NormalT(nullptr), m_RoughnessT(nullptr), m_OcclusionT(nullptr), m_OpacityT(nullptr)
	{
	}

	Material::Material(const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& ambient, float shininess)
		: m_Diffuse(diffuse), m_Specular(specular), m_Ambient(ambient), m_Shininess(shininess)
		, m_DiffuseT(nullptr), m_SpecularT(nullptr), m_NormalT(nullptr), m_RoughnessT(nullptr), m_OcclusionT(nullptr), m_OpacityT(nullptr)
	{
	}

	void Material::Bind() const
	{
		for (const auto & x : m_ActiveTextures)
		{
			x->Bind();
		}
	}

	void Material::DetachActiveTexture(std::shared_ptr<Texture2D>& texture)
	{
		for (auto it = m_ActiveTextures.begin(); it != m_ActiveTextures.end(); ++it)
		{
			if (*it == texture)
			{
				m_ActiveTextures.erase(it);
				texture = nullptr;
				return;
			}
		}
	}

	void Material::SetDiffuse(const glm::vec3& diffuse)
	{
		m_Diffuse = diffuse;
		if (m_DiffuseT != nullptr) DetachActiveTexture(m_DiffuseT);
	}

	void Material::SetDiffuse(std::shared_ptr<Texture2D> diffuse)
	{
		if (m_DiffuseT != nullptr) DetachActiveTexture(m_DiffuseT);
		m_DiffuseT = std::move(diffuse);
		if (m_DiffuseT != nullptr) m_ActiveTextures.emplace_back(m_DiffuseT);
	}

	void Material::SetSpecular(const glm::vec3& specular)
	{
		m_Specular = specular;
		if (m_SpecularT != nullptr) DetachActiveTexture(m_SpecularT);
	}

	void Material::SetSpecular(std::shared_ptr<Texture2D> specular)
	{
		if (m_SpecularT != nullptr) DetachActiveTexture(m_SpecularT);
		m_SpecularT = std::move(specular);
		if (m_SpecularT != nullptr) m_ActiveTextures.emplace_back(m_SpecularT);
	}

	void Material::SetAmbient(const glm::vec3& ambient)
	{
		m_Ambient = ambient;
	}

	void Material::SetShininess(float shininess)
	{
		m_Shininess = shininess;
	}

	void Material::SetNormal(std::shared_ptr<Texture2D> normal)
	{
		if (m_NormalT != nullptr) DetachActiveTexture(m_NormalT);
		m_NormalT = std::move(normal);
		if (m_NormalT != nullptr) m_ActiveTextures.emplace_back(m_NormalT);
	}

	void Material::SetRoughness(std::shared_ptr<Texture2D> roughness)
	{
		if (m_RoughnessT != nullptr) DetachActiveTexture(m_RoughnessT);
		m_RoughnessT = std::move(roughness);
		if (m_RoughnessT != nullptr) m_ActiveTextures.emplace_back(m_RoughnessT);
	}

	void Material::SetOcclusion(std::shared_ptr<Texture2D> occlusion)
	{
		if (m_OcclusionT != nullptr) DetachActiveTexture(m_OcclusionT);
		m_OcclusionT = std::move(occlusion);
		if (m_OcclusionT != nullptr) m_ActiveTextures.emplace_back(m_OcclusionT);
	}

	void Material::SetOpacity(std::shared_ptr<Texture2D> opacity)
	{
		if (m_OpacityT != nullptr) DetachActiveTexture(m_OpacityT);
		m_OpacityT = std::move(opacity);
		if (m_OpacityT != nullptr) m_ActiveTextures.emplace_back(m_OpacityT);
	}

}