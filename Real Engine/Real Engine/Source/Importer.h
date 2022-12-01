#pragma once
#include "Log.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <DevIL/il.h>
#include "Mesh.h"
#include "Material.h"
#include "TextureLoader.h"
#include "Entity.h"
#include "GameObject.h"
#include "Resource.h"
#include "ResourcesManagement.h"

/*
	Importer will import any type of files
	From assets folder or drag dropped files
*/

class Importer : public Module
{
public:
	Importer();
	Importer(bool isActive);
	~Importer();

	bool Awake();
	bool Start();

	std::string directory;
	std::string fileName;
	std::vector<Texture>loadedtextures;
	std::vector<Texture>ImportedTextures;
};


namespace TextureImporter {
	Texture* Load(const std::string& filename);
	void Save(const Texture mat, const std::string& filename);
	void Import(Resource* resource);
	std::vector<Texture> Import(const aiMaterial* mat, aiTextureType type, std::string typeName);
}
namespace MaterialImporter {
	void Load(const std::string& filename);
	void Load(const Material* mat, const std::string& filename);
	void Save(const Material mat, const std::string& filename);
	void Import(const aiMaterial* material, Material* ourMaterial);
}
namespace MeshImporter {
	void Load(const std::string& filename);
	void Save(const Mesh mesh, const std::string& filename);
	Mesh* Import(const aiMesh* mesh);
}
namespace FbxImporter {
	static std::string fbxName;
	void Import(const std::string& file_path);
	void ProcessNode(aiNode* node, const aiScene* scene, vector<Mesh>* meshes);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
}

