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

	// when dropping anything on the app 
	// read file type and store it,
	// if dropped on scene and its a FBX load as obj
	void OnDrop(const std::string file_path);

	Resource::Type FilterFile(const std::string file_path);

	bool ImportFile(const std::string file_path);
	//void ProcessNode(aiNode* node, const aiScene* scene, vector<Mesh>* meshes);
	//Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	//Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::string directory;
	std::string fileName;
	std::vector<Texture>loadedtextures;


};

namespace MaterialImporter {
	void Load();
	void Save();
	void Import(const aiMaterial* material, Material* ourMaterial);
}
namespace TextureImporter {
	void Load();
	void Save();
	std::vector<Texture> Import(const aiMaterial* mat, aiTextureType type, std::string typeName);
}
namespace MeshImporter {
	void Load();
	void Save(const Mesh mesh, const std::string& filename);
	void Import(const aiMesh* mesh, Mesh* ourMaterial);
}
namespace FbxImporter {
	void Import(const std::string& file_path);
	void ProcessNode(aiNode* node, const aiScene* scene, vector<Mesh>* meshes);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
}

