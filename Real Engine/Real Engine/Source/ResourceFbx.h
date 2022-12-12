#pragma once
#include "Resource.h"
#include "GameObject.h"
#define MAX_CHILDS 100
struct FbxNode {
	std::string name = "Unamed";
	mat4x4 transfom;
	FbxNode* parent = nullptr;
	vector<FbxNode> childs;
	unsigned int childsCount = 0;
	vector<unsigned int> meshIndex;//array of indices to the mesh used
	unsigned int meshCount;//number of meshes used by the node
};

class ResourceFbx : public Resource
{
public :
    ResourceFbx(UID uid);
    ~ResourceFbx();


	void Save()const;
	void Load()const;
	void UnLoad()const;

	static void Load(std::shared_ptr<Resource>& resource, std::ifstream& data);

	FbxNode GetRoot() const{ return *root; };
	FbxNode* root;
	//sotre all materials used by the obj
	vector<UID> materials;
	//sotre all meshes used by the obj
	vector<UID> meshes;
};

