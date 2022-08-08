//----------------------------------------------------------------------------------------
/**
 * \file       EntityShader.hpp
 * \author     Richard Kvasnica
 * \brief      Child class entity shader declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "ShaderProgram.hpp"

#include <Scene/PortalWalls.hpp>
#include <Scene/GameObject.hpp>
#include <Scene/Light.hpp>

namespace kvasnric
{
	// Child class of a Shader Program class. Expands functionality to basic entity shading.
	class EntityShader final : public ShaderProgram
	{
	public:
		/**
		 * Constructs a new entity shader program by compiling two inputting source strings
		 * @param vertexSrc glsl source code string of vertex shader
		 * @param fragSrc glsl source code string of fragment shader
		 */
		EntityShader(const std::string& vertexSrc, const std::string& fragSrc);
		~EntityShader() override = default;

		/**
		 * Renders GameObject instance
		 * @param obj const reference to a GameObject instance
		 */
		void RenderGameObject(const GameObject& obj) const;

		/**
		 * Renders GameObject instance with additional transformation
		 * @param obj const reference to a GameObject instance
		 * @param transform mat4 that applies additional transformation to a model matrix
		 */
		void RenderGameObject(const GameObject& obj, const glm::mat4& transform) const;

		/**
		 * Renders transparent GameObject instance
		 * @param obj const reference to a GameObject instance
		 */
		void RenderTransparentGameObject(const GameObject& obj) const;
		
		/**
		 * Renders Model instance
		 * @param m const reference to a Model instance
		 */
		void RenderModel(const Model& m) const;

		/**
		 * Renders Mesh instance
		 * @param m const reference to a Mesh instance
		 */
		void RenderMesh(const Mesh& m) const;

		/**
		 * Renders Hardcoded Portal Walls instance
		 * @param pw const reference to a Hardcoded Portal Walls instance
		 * @param model nothing should be done unless special case
		 */
		void RenderPortalWalls(const PortalWalls& pw, const glm::mat4& model = UNIT_MATRIX) const;
		
		/**
		 * Uploads to shader info about camera view
		 * @param pos position of the view
		 * @param view 4x4 transformation matrix from world coordinate system to camera
		 * @param projection 4x4 transformation matrix from camera coordinate system to projection
		 */
		void UploadViewInfo(const glm::vec3& pos, const glm::mat4& view, const glm::mat4& projection) const;

		/**
		 * Uploads one point light into shader. Can be used max LIGHT_SOURCE times. Through uniforms.
		 */
		void UploadPointLight(const PointLight& point);

		/**
		 * Uploads one spot light into shader. Can be use max LIGHT_SOURCE times. Through uniforms.
		 */
		void UploadSpotLight(const SpotLight& spot);

		/**
		 * Uploads model matrix into the shader through uniforms.
		 */
		void UploadModelMatrix(const glm::mat4& model) const;

		/**
		 * Uploads material properties into shader. Through uniforms.
		 */
		void UploadMaterialProperties(const Material& material) const;

		/**
		 * Uploads color of a sky
		 */
		void UploadSkyColor(const glm::vec3 & sky) const;
		
		/**
		 * Toggles fog and sends a bool to a shader whether it should be rendered.
		 */
		void ToggleFog();

		/**
		 * Returns whether the fog is enabled
		 */
		inline bool IsFogEnabled() const { return m_Fog; }
	private:

		/**
		 * Accesses every uniform in entity shader and assigns its location. Used with init lights.
		 */
		void InitUniformLocations();

		/**
		 * Accesses every light uniform in entity shader and assigns its location.
		 */
		void InitLights();

		/**
		 * Sends to shaders texture samplers texture slot of each texture type.
		 */
		void InitTextureSamplers() const;
		
		short m_PointLightCnt;
		short m_SpotLightCnt;
		bool m_Fog;

		static const int LIGHT_SOURCES = 10;

		// every struct is the same as the entity shader uniforms

		// struct holding material properties
		struct MaterialLocation
		{
			int ambient;
			int diffuse;
			int specular;
			int shininess;
		};

		// struct holding point light properties
		struct PointLight
		{
			int position;
			int diffuse;
			int specular;
			int ambient;
			int intensity;
			int attenuation;
		};

		// struct holding spot light properties
		struct SpotLight
		{
			int position;
			int direction;
			int diffuse;
			int specular;
			int cutOff;
		};

		// struct holding texture binded slot and bool whether texture should be used.
		struct TextureLocation
		{
			int source;
			int enabled;
		};

		// struct holding all fragment shader uniforms
		struct FragUniforms
		{
			MaterialLocation material;
			TextureLocation t_Diffuse;
			TextureLocation t_Specular;
			TextureLocation t_Normal;
			TextureLocation t_Roughness;
			TextureLocation t_Occlusion;
			TextureLocation t_Opacity;
			PointLight point[LIGHT_SOURCES];
			SpotLight spot[LIGHT_SOURCES];
			int pointLights;
			int spotLights;
			int cubeMap;
			int skyColor;
		};

		// struct holding all vertex shader uniforms
		struct VertUniforms
		{
			int ViewPosition;
			int Projection;
			int View;
			int Model;
			int Fog;
		};
		
		FragUniforms fu;
		VertUniforms vu;
	};
}