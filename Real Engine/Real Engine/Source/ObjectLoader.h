#pragma once
#include "Log.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
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

	bool LoadObject(const std::string file_path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	std::string directory;
	std::vector<Texture>loadedtextures;
	Entity newEntity;

	std::string fileName;
};

