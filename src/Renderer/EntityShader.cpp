//----------------------------------------------------------------------------------------
/**
 * \file       EntityShader.hpp
 * \author     Richard Kvasnica
 * \brief      Child class entity shader definition
*/
//----------------------------------------------------------------------------------------

#include "EntityShader.hpp"

namespace kvasnric
{
	EntityShader::EntityShader(const std::string& vertexSrc, const std::string& fragSrc)
		: ShaderProgram(vertexSrc, fragSrc), m_PointLightCnt( 0 ), m_SpotLightCnt( 0 ), m_Fog( false )
	{
		InitUniformLocations();
		InitTextureSamplers();
		Unbind();
	}

	void EntityShader::RenderGameObject(const GameObject& obj) const
	{
		// uploads model matrix first then, renders model inside gameobject
		UploadModelMatrix(obj.GetModelMatrix());
		RenderModel(obj.GetModel());
	}

	void EntityShader::RenderGameObject(const GameObject& obj, const glm::mat4& transform) const
	{
		UploadModelMatrix(transform*obj.GetModelMatrix());
		RenderModel(obj.GetModel());
	}

	
	void EntityShader::RenderTransparentGameObject(const GameObject& obj) const
	{
		// renders object exactly twice. First time with culling to back faces and then to front faces.
		UploadModelMatrix(obj.GetModelMatrix());

		EnableBlending();
		RenderBackFace();
		RenderModel(obj.GetModel());
		RenderFrontFace();
		RenderModel(obj.GetModel());
		DisableBlending();
	}

	void EntityShader::RenderModel(const Model& m) const
	{
		// renders each mesh in model
		for (const auto& mesh : m.GetMeshes())
		{
			RenderMesh(*mesh);
		}
	}

	void EntityShader::RenderMesh(const Mesh& m) const
	{
		// bind mesh, upload its material properties and render
		m.Bind();
		UploadMaterialProperties(m.GetMaterial());
		RenderElements(0, m.GetCountOfIndices());
	}

	void EntityShader::RenderPortalWalls(const PortalWalls& pw, const glm::mat4& model) const
	{
		UploadModelMatrix(model);
		RenderModel(pw);
	}

	void EntityShader::ToggleFog()
	{
		Bind();
		m_Fog = !m_Fog;
		SetUniform1i(vu.Fog, m_Fog);
	}
	
	void EntityShader::UploadViewInfo(const glm::vec3& pos, const glm::mat4& view, const glm::mat4& projection) const
	{
		SetUniform3f(vu.ViewPosition, pos);
		SetUniformMat4(vu.View, view);
		SetUniformMat4(vu.Projection, projection);
	}

	void EntityShader::UploadPointLight(const kvasnric::PointLight& point)
	{
		SetUniform3f(fu.point[m_PointLightCnt].position, point.GetPosition());
		SetUniform3f(fu.point[m_PointLightCnt].diffuse, point.GetDiffuse());
		SetUniform3f(fu.point[m_PointLightCnt].specular, point.GetSpecular());
		SetUniform3f(fu.point[m_PointLightCnt].ambient, point.GetAmbient());
		SetUniform1f(fu.point[m_PointLightCnt].intensity, point.GetIntensity());
		SetUniform2f(fu.point[m_PointLightCnt].attenuation, point.GetAttenuation());

		SetUniform1i(fu.pointLights, ++m_PointLightCnt);
	}

	void EntityShader::UploadSpotLight(const kvasnric::SpotLight& spot)
	{
		SetUniform3f(fu.spot[m_SpotLightCnt].position, spot.GetPosition());
		SetUniform3f(fu.spot[m_SpotLightCnt].diffuse, spot.GetDiffuse());
		SetUniform3f(fu.spot[m_SpotLightCnt].specular, spot.GetSpecular());
		SetUniform2f(fu.spot[m_SpotLightCnt].cutOff, spot.GetCutOff());
		SetUniform3f(fu.spot[m_SpotLightCnt].direction, spot.GetDirection());

		SetUniform1i(fu.spotLights, ++m_SpotLightCnt);
	}

	void EntityShader::UploadModelMatrix(const glm::mat4& model) const
	{
		SetUniformMat4(vu.Model, model);
	}

	void EntityShader::UploadMaterialProperties(const Material& material) const
	{
		SetUniform3f(fu.material.diffuse, material.GetDiffuse());
		SetUniform3f(fu.material.specular, material.GetSpecular());
		SetUniform3f(fu.material.ambient, material.GetAmbient());
		SetUniform1f(fu.material.shininess, material.GetShininess());

		SetUniform1i(fu.t_Diffuse.enabled, material.IsDiffuseTextureActive());
		SetUniform1i(fu.t_Specular.enabled, material.IsSpecularTextureActive());
		SetUniform1i(fu.t_Normal.enabled, material.IsNormalTextureActive());
		SetUniform1i(fu.t_Roughness.enabled, material.IsGlossyTextureActive());
		SetUniform1i(fu.t_Occlusion.enabled, material.IsOcclusionTextureActive());
		SetUniform1i(fu.t_Opacity.enabled, material.IsOpacityTextureActive());
	}

	void EntityShader::UploadSkyColor(const glm::vec3& sky) const
	{
		SetUniform3f(fu.skyColor, sky);
	}

	
	void EntityShader::InitUniformLocations()
	{
		AssignLocation(vu.View);
		AssignLocation(vu.Projection);
		AssignLocation(vu.Model);

		AssignLocation(vu.ViewPosition);

		AssignLocation(vu.Fog);
		SetUniform1i(vu.Fog, m_Fog);
		
		InitLights();

		AssignLocation(fu.material.diffuse);
		AssignLocation(fu.material.specular);
		AssignLocation(fu.material.ambient);
		AssignLocation(fu.material.shininess);

		AssignLocation(fu.t_Diffuse.source);
		AssignLocation(fu.t_Diffuse.enabled);

		AssignLocation(fu.t_Specular.source);
		AssignLocation(fu.t_Specular.enabled);

		AssignLocation(fu.t_Normal.source);
		AssignLocation(fu.t_Normal.enabled);

		AssignLocation(fu.t_Roughness.source);
		AssignLocation(fu.t_Roughness.enabled);

		AssignLocation(fu.t_Occlusion.source);
		AssignLocation(fu.t_Occlusion.enabled);

		AssignLocation(fu.t_Opacity.source);
		AssignLocation(fu.t_Opacity.enabled);
		
		AssignLocation(fu.cubeMap);
		AssignLocation(fu.skyColor);
	}

	void EntityShader::InitLights()
	{
		AssignLocation(fu.pointLights);
		AssignLocation(fu.spotLights);

		for (int i = 0; i < LIGHT_SOURCES; ++i)
		{
			std::string name = "fu.point[" + std::to_string(i) + "]";
			fu.point[i].position = GetUniformLocation((name + ".position").c_str());
			fu.point[i].diffuse = GetUniformLocation((name + ".diffuse").c_str());
			fu.point[i].specular = GetUniformLocation((name + ".specular").c_str());
			fu.point[i].ambient = GetUniformLocation((name + ".ambient").c_str());
			fu.point[i].intensity = GetUniformLocation((name + ".intensity").c_str());
			fu.point[i].attenuation = GetUniformLocation((name + ".attenuation").c_str());
		}

		for (int i = 0; i < LIGHT_SOURCES; ++i)
		{
			std::string name = "fu.spot[" + std::to_string(i) + "]";
			fu.spot[i].position = GetUniformLocation((name + ".position").c_str());
			fu.spot[i].diffuse = GetUniformLocation((name + ".diffuse").c_str());
			fu.spot[i].specular = GetUniformLocation((name + ".specular").c_str());
			fu.spot[i].direction = GetUniformLocation((name + ".direction").c_str());
			fu.spot[i].cutOff = GetUniformLocation((name + ".cutOff").c_str());
		}

		SetUniform1i(fu.pointLights, 0);
		SetUniform1i(fu.spotLights, 0);
	}

	void EntityShader::InitTextureSamplers() const
	{
		// assign each texture type its texture slot
		
		SetUniform1i(fu.t_Diffuse.source, Texture2D::DIFFUSE);
		SetUniform1i(fu.t_Diffuse.enabled, false);
		
		SetUniform1i(fu.t_Specular.source, Texture2D::SPECULAR);
		SetUniform1i(fu.t_Specular.enabled, false);

		SetUniform1i(fu.t_Normal.source, Texture2D::NORMAL);
		SetUniform1i(fu.t_Normal.enabled, false);

		SetUniform1i(fu.t_Roughness.source, Texture2D::ROUGHNESS);
		SetUniform1i(fu.t_Roughness.enabled, false);

		SetUniform1i(fu.t_Occlusion.source, Texture2D::OCCLUSION);
		SetUniform1i(fu.t_Occlusion.enabled, false);

		SetUniform1i(fu.t_Opacity.source, Texture2D::OPACITY);
		SetUniform1i(fu.t_Opacity.enabled, false);
		
		SetUniform1i(fu.cubeMap, Texture2D::CUBEMAP);
	}
}
