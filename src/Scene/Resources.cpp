//----------------------------------------------------------------------------------------
/**
 * \file       Resources.cpp
 * \author     Richard Kvasnica
 * \brief      Resources class definition
*/
//----------------------------------------------------------------------------------------

#include "Resources.hpp"

#include <iostream>
#include <sstream>

#include "pgr.h"

namespace kvasnric
{
	void Resources::LoadModels(const std::vector<std::string>& files)
	{
		for (const auto & file : files)
		{
			if (m_Models.find(file) == m_Models.end())
			{
				m_Models.insert({ file, std::shared_ptr<Model>(LoadModelFromFile(file)) });
			}
		}
	}

	void Resources::LoadCubeMap(const std::string& name)
	{
		m_CubeMap.reset(new CubeMap(name));
	}

	void Resources::LoadCubeMapShader()
	{
		m_CubeMapShader.reset(new CubeMapShader());
	}

	void Resources::LoadStencilStampTester()
	{
		m_StencilStamp.reset(new StencilStamp());
	}

	void Resources::LoadShader(const std::string& file)
	{
		const auto vsSrc = ShaderProgram::ReadShaderFromFile("res/shaders/" + file + ".vert");
		const auto fsSrc = ShaderProgram::ReadShaderFromFile("res/shaders/" + file + ".frag");

		m_Shader.reset(new ShaderProgram(vsSrc, fsSrc));
	}

	void Resources::LoadEntityShader()
	{
		const auto vsSrc = ShaderProgram::ReadShaderFromFile("res/shaders/entity.vert");
		const auto fsSrc = ShaderProgram::ReadShaderFromFile("res/shaders/entity.frag");

		m_Entity.reset(new EntityShader(vsSrc, fsSrc));
	}

	void Resources::LoadPortals()
	{
		m_PortalTexture.reset(new PortalTextureShader());
	}

	std::shared_ptr<Model> Resources::operator[](const std::string& name)
	{
		const auto it = m_Models.find(name);
		
		if (it == m_Models.end())
		{
			const auto res = m_Models.insert({ name, std::shared_ptr<Model>(LoadModelFromFile(name)) });
			return res.first->second;
		}
		
		return it->second;
	}

	
	Model* Resources::LoadModelFromFile(const std::string& filename)
	{
		Assimp::Importer importer;

		const std::string filepath = "res/models/" + filename;

		// load model file into assimp structure
		const auto* scene = importer.ReadFile(filepath,
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs | 
			aiProcess_CalcTangentSpace |
			aiProcess_PreTransformVertices |
			aiProcess_MakeLeftHanded |
			aiProcess_JoinIdenticalVertices |
			aiProcess_OptimizeMeshes
		);

		auto* m = new Model();

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::stringstream s;
			s << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;

			throw std::runtime_error(s.str().c_str());
		}

		m->SetDirectory(filepath.substr(0, filepath.find_last_of('/')));
		
		// recurse into the assimp node tree
		ProcessNode(*m, scene->mRootNode, scene);

		return m;
	}

	void Resources::ProcessNode(Model & model, aiNode* node, const aiScene* scene)
	{
		// if the node has meshes. Copy mesh data into new mesh and add this mesh into the model.
		for (unsigned i = 0; i < node->mNumMeshes; ++i)
		{
			ProcessMesh(model, scene->mMeshes[node->mMeshes[i]], scene);
		}

		// if the node has more nodes recurse into them.
		for (unsigned i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(model, node->mChildren[i], scene);
		}
	}

	void Resources::ProcessMesh(Model & model, aiMesh* mesh, const aiScene* scene)
	{
		auto& m = model.NewMesh();

		for (unsigned i = 0; i < mesh->mNumVertices; ++i)
		{
			const auto& vert = mesh->mVertices[i];
			const auto& norm = mesh->mNormals[i];

			Vertex v{
				{ vert.x, vert.y, vert.z },
				{ norm.x, norm.y, norm.z },
				{ 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f }
			};

			// if vertex has texture coordinates it will surely have tangents
			if (mesh->HasTextureCoords(0))
			{
				const auto& tex = mesh->mTextureCoords[0][i];
				const auto& tang = mesh->mTangents[i];

				v.TexCoords.x = tex.x; v.TexCoords.y = tex.y;
				v.Tangent.x = tang.x; v.Tangent.y = tang.y; v.Tangent.z = tang.z;
			}

			m.AddVertex(v);
		}

		for (unsigned i = 0; i < mesh->mNumFaces; ++i)
		{
			const auto& face = mesh->mFaces[i].mIndices;
			m.AddFace(face[0], face[1], face[2]);
		}

		ProcessMaterial(m, scene->mMaterials[mesh->mMaterialIndex]);

		m.RegisterMesh();
	}

	Material Resources::CreateMaterial(const aiMaterial* material)
	{
		aiString str;
		aiColor4D color;
		const aiColor4D null(0.0f, 0.0f, 0.0f, 0.0f);
		ai_real shininess, strength;
		aiReturn retValue = AI_SUCCESS;
		unsigned max = 1;

		material->Get(AI_MATKEY_NAME, str);

		std::cout << "Material: " << str.data << std::endl;

		if ((retValue = aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color)) != AI_SUCCESS)
			color = null;
		const glm::vec3 diffuse = { color.r, color.g, color.b };

		if ((retValue = aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color)) != AI_SUCCESS)
			color = null;
		const glm::vec3 specular = { color.r, color.g, color.b };

		if ((retValue = aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color)) != AI_SUCCESS)
			color = null;
		const glm::vec3 ambient = { color.r, color.g, color.b };

		if ((retValue = aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max)) != AI_SUCCESS)
			shininess = 1.0f;
		max = 1;
		if ((retValue = aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS_STRENGTH, &strength, &max)) != AI_SUCCESS)
			strength = 1.0f;

		return Material(diffuse, specular, ambient, shininess * strength);
	}


	void Resources::ProcessMaterial(Mesh& mesh, const aiMaterial* material)
	{
		// create new material from assimp
		auto mat = std::make_unique<Material>(CreateMaterial(material));

		// set each texture to its rightful slot
		mat->SetDiffuse(GetTexture(material, aiTextureType_DIFFUSE));
		mat->SetSpecular(GetTexture(material, aiTextureType_SPECULAR));
		mat->SetNormal(GetTexture(material, aiTextureType_HEIGHT));
		mat->SetRoughness(GetTexture(material, aiTextureType_SHININESS));
		mat->SetOcclusion(GetTexture(material, aiTextureType_AMBIENT));
		mat->SetOpacity(GetTexture(material, aiTextureType_OPACITY));
		
		mesh.AssignMaterial(std::move(mat));
	}

	std::shared_ptr<Texture2D> Resources::GetTexture(const std::string& name, Texture2D::TYPE type)
	{
		const auto it = m_Textures.find(name);

		if (it == m_Textures.end())
		{
			return m_Textures.insert({ name, std::make_shared<Texture2D>(name, type) }).first->second;
		}

		return it->second;
	}

	
	std::shared_ptr<Texture2D> Resources::GetTexture(const aiMaterial* material, aiTextureType type)
	{
		// if the material has this type of texture process it.
		if (material->GetTextureCount(type) != 1) return nullptr;

		aiString str;
		// get texture string from assimp
		material->GetTexture(type, 0, &str);
		std::string filename = str.data;

		std::cout << "Texture: " << str.data << std::endl;

		// translate assimp texture type into out internal texture type enum
		Texture::TYPE texT;
		switch (type)
		{
		case aiTextureType_DIFFUSE: texT = Texture::DIFFUSE; break;
		case aiTextureType_SPECULAR: texT = Texture::SPECULAR; break;
		case aiTextureType_HEIGHT: texT = Texture::NORMAL; break;
		case aiTextureType_SHININESS: texT = Texture::ROUGHNESS; break;
		case aiTextureType_AMBIENT: texT = Texture::OCCLUSION; break;
		case aiTextureType_OPACITY: texT = Texture::OPACITY; break;
		default: throw std::runtime_error("Trying to read a texture of unsupported or unknown type.");
		}

		// load the texture
		return GetTexture(filename, texT);
	}
}