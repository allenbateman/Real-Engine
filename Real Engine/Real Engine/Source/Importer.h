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



namespace MaterialImporter {
	void Import();
	bool Save();
	bool Load();
};
namespace MeshImporter {
	void Import();
	bool Save();
	bool Load();
};

class Importer
{
public:
	Importer();
	~Importer();
	
	// when dropping anything on the app 
	// read file type and store it,
	// if dropped on scene and its a FBX load as obj
	void OnDrop(const std::string file_path);

	// Change file format to own file format
	// Save file

	bool SaveMaterial();
	bool SaveMesh();

	bool LoadMesh();
	bool LoadMaterial();



	vector<GameObject*> LoadObject(const std::string file_path);
	void ProcessNode(aiNode* node, const aiScene* scene, GameObject parentGo, std::vector<GameObject*>& result);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, GameObject go);
	Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::string directory;
	std::string fileName;
	std::vector<Texture>loadedtextures;

};