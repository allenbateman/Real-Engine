#pragma once
//utils
#include "Log.h"
#include "TextureLoader.h"

//libs
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <DevIL/il.h>
//App modules
#include "Entity.h"
#include "GameObject.h"
#include "ResourcesManagement.h"
//components
#include "Mesh.h"
#include "Material.h"
//resources
#include "Resource.h"
#include "ResourceScene.h"
#include "ResourceMaterial.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"

//using pathList = std::vector<std::string>;
using pathList = std::vector<std::filesystem::path>;
class Importer : public Module
{
public:
	Importer();
	Importer(bool isActive);
	~Importer();

	bool Awake();
	bool Start();
	pathList importedTextures{};
	//of the materials to keep track of them, we will store the asset path, where do they comefrom
	//and if it belongs to any scene we need to know the index
	std::map<string, std::pair<int, UID>>importedMaterials{};
	std::map<string, std::pair<int, UID>>importedMeshes{};
};


namespace TextureImporter {
	void Import(shared_ptr<Resource>& resource);
	void Save(const Texture mat, const std::string& filename);
	bool LoadAiMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, shared_ptr<Resource>& resourceMat);
}
namespace MaterialImporter {
	void Import(const aiMaterial* material, shared_ptr<ResourceMaterial>& resourceMat);
	void Load(const Material* mat, const std::string& filename);
	void Save(const shared_ptr<ResourceMaterial>& mat, const std::string& filename);
}
namespace MeshImporter { 
	void Import(const aiMesh* mesh, shared_ptr<ResourceMesh>& resource);
	void Load(const std::string& filename);
	void Save(const shared_ptr<ResourceMesh>& mesh, const std::string& filename);
}
namespace SceneImporter {
	void Import(shared_ptr<Resource>& resource);
	void ProcessaNode(aiNode* node, const aiScene* scene, GameObject* rNode,shared_ptr<ResourceScene>& rFbx);
	void ProcessaMesh(aiMesh* mesh, const aiScene* scene, GameObject* rNode, shared_ptr<ResourceScene>& rFbx);
	UID ProcessMaterial(aiMesh* mesh, const aiScene* scene, GameObject* rNode, shared_ptr<ResourceScene>& rFbx);
	void Save(const GameObject scene, const std::string& filename);

	void LoadObject(const std::string file_path);
	void ProcessNode(aiNode* node, const aiScene* scene,GameObject* go, shared_ptr<ResourceScene>& rFbx);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, GameObject* go);
	Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
}

