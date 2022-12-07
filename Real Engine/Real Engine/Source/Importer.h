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

using pathList = std::vector<std::string>;
class Importer : public Module
{
public:
	Importer();
	Importer(bool isActive);
	~Importer();

	bool Awake();
	bool Start();
	pathList importedTextures{};
};


namespace TextureImporter {
	Resource* Import(Resource* resource);
	void Import(const aiTexture* texture,Resource* resource);
	void Save(const Texture mat, const std::string& filename);
}
namespace MaterialImporter {
	void Import(const aiMaterial* material, Resource* resource);
	Resource* Import(Resource* resource);
	void Load(const Material* mat, const std::string& filename);
	void Save(const Material mat, const std::string& filename);
}
namespace MeshImporter { 
	Mesh* Import(const aiMesh* mesh, Resource* resource);
	Resource* Import(Resource* resource);
	void Load(const std::string& filename);
	void Save(const Mesh mesh, const std::string& filename);
}
namespace FbxImporter {
	void Import(Resource* resource);
	void ProcessaNode(aiNode* node, const aiScene* scene, ResourceFbx* resourceFbx);
	void ProcessaMesh(aiMesh* mesh, const aiScene* scene);
	void ProcessMaterial(aiMesh* mesh, const aiScene* scene);
}

