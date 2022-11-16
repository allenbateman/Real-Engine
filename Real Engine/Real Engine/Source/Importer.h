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

static const char* Library = "Library";

class Importer : public Module , public System
{
public:
	Importer();
	Importer(bool isActive);
	~Importer();

	bool Awake();
	bool Start();
	void HandleEvent(Event* e);

	// when dropping anything on the app 
	// read file type and store it,
	// if dropped on scene and its a FBX load as obj
	void OnDrop(const std::string file_path);

	// Change file format to own file format
	// Save file


	bool SaveObject();
	bool SaveMaterial();
	bool SaveMesh();

	GameObject LoadObjet();
	Mesh LoadMesh();
	Material LoadMaterial();

	bool ProcessFile(const std::string file_path);



	vector<GameObject*> LoadObject(const std::string file_path);
	void ProcessNode(aiNode* node, const aiScene* scene, GameObject parentGo, std::vector<GameObject*>& result);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, GameObject go);
	Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
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
namespace MeshImporter {
	void Load();
	void Save();
	void Import();
}