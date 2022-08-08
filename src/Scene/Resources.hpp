//----------------------------------------------------------------------------------------
/**
 * \file       Resources.hpp
 * \author     Richard Kvasnica
 * \brief      Resources class declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Model.hpp"
#include <memory>
#include <Renderer/EntityShader.hpp>
#include <Scene/Cubemap.hpp>
#include <Renderer/PortalTextureShader.hpp>
#include <Renderer/StencilStamp.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace kvasnric
{
	// Loads all my resources into different structures
	class Resources
	{
	public:
		Resources() = default;
		~Resources() = default;

		// Loads different types of shader programs
		void LoadShader(const std::string& file);
		void LoadEntityShader();
		void LoadModels(const std::vector<std::string>& files);
		void LoadCubeMap(const std::string& name);
		void LoadCubeMapShader();
		void LoadStencilStampTester();
		void LoadPortals();

		/**
		 * If the model is already loaded it returns it from the unordered map od models
		 * Othewise it will load the model, assign it to unordered map and return the model pointer.
		 */
		std::shared_ptr<Model> operator[](const std::string& name);

		/**
		 * Does exactly the same as model loading except for texture2D pointers.
		 */
		std::shared_ptr<Texture2D> GetTexture(const std::string& name, Texture2D::TYPE type );

		// Shader getters
		inline EntityShader& Entity() const { return *m_Entity; }
		inline ShaderProgram& Shader() const { return *m_Shader; }
		inline CubeMap& Cubemap() const { return *m_CubeMap; }
		inline CubeMapShader& CubemapShader() const { return *m_CubeMapShader; }
		inline PortalTextureShader& PortalTexture() const { return *m_PortalTexture; }
		inline StencilStamp& Stencil() const { return *m_StencilStamp; }
	private:
		/**
		 * Constructs a new Model by loading it and returns its pointer.
		 */
		Model* LoadModelFromFile(const std::string& filename);

		/**
		 * Process one hierarchical node of assimp loader
		 */
		void ProcessNode(Model& model, aiNode* node, const aiScene* scene);

		/**
		 * Shift mesh data from assimp into our mesh instances
		 */
		void ProcessMesh(Model& model, aiMesh* mesh, const aiScene* scene);

		/**
		 * Shift material data and textures from assimp into out structures.
		 */
		void ProcessMaterial(Mesh& mesh, const aiMaterial* material);

		/**
		 * Creates new material from assimp structure
		 */
		static Material CreateMaterial(const aiMaterial* material);

		/**
		 * Same mechanism as public get texture method, but this prevents from loading the same texture twice.
		 */
		std::shared_ptr<Texture2D> GetTexture(const aiMaterial* material, aiTextureType type);

		std::unordered_map<std::string, std::shared_ptr<Model>> m_Models;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures;
		
		std::unique_ptr<CubeMap> m_CubeMap;
		std::unique_ptr<ShaderProgram> m_Shader;
		std::unique_ptr<CubeMapShader> m_CubeMapShader;
		std::unique_ptr<EntityShader> m_Entity;
		std::unique_ptr<PortalTextureShader> m_PortalTexture;
		std::unique_ptr<StencilStamp> m_StencilStamp;
		
	};
}
