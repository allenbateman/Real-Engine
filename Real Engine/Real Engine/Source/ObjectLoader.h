#pragma once
#include "Log.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Material.h"
#include "TextureLoader.h"
#include "Entity.h"
#include "GameObject.h"

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	vector<GameObject*> LoadObject(const std::string file_path);
	void ProcessNode(aiNode* node, const aiScene* scene, GameObject parentGo, std::vector<GameObject*>& result);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, GameObject go);
	Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::string directory;
	std::string fileName;
	std::vector<Texture>loadedtextures;
};

