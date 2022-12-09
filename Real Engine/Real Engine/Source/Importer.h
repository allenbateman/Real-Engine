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
#include "ResourceFbx.h"
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
	std::vector<std::pair<int,std::filesystem::path>>importedMaterials;
};


namespace TextureImporter {
	shared_ptr<Resource> Import(shared_ptr<Resource> resource);
	void Import(const aiTexture* texture, shared_ptr<Resource> resource);
	void Save(const Texture mat, const std::string& filename);
}
namespace MaterialImporter {
	int Import(const aiMaterial* material, shared_ptr<Resource> resource);
	shared_ptr<Resource> Import(shared_ptr<Resource> resource);
	void Load(const Material* mat, const std::string& filename);
	void Save(const Material mat, const std::string& filename);
}
namespace MeshImporter { 
	Mesh* Import(const aiMesh* mesh, shared_ptr<Resource> resource);
	shared_ptr<Resource> Import(shared_ptr<Resource> resource);
	void Load(const std::string& filename);
	void Save(const Mesh mesh, const std::string& filename);
}
namespace FbxImporter {
	void Import(shared_ptr<Resource> resource);
	void ProcessaNode(aiNode* node, const aiScene* scene, shared_ptr<ResourceFbx> resourceFbx);
	void ProcessaMesh(aiMesh* mesh, const aiScene* scene);
	int ProcessMaterial(aiMesh* mesh, const aiScene* scene);
}

