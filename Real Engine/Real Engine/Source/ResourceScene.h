#pragma once
#include "Resource.h"
#include "GameObject.h"

#define MAX_CHILDS 100
//struct SceneNode {
//	std::string name = "Unamed";
//	mat4x4 transfom;
//	SceneNode* parent = nullptr;
//	vector<SceneNode> childs;
//	unsigned int childsCount = 0;
//	vector<unsigned int> meshIndex;//array of indices to the mesh used
//	unsigned int meshCount;//number of meshes used by the node
//};

class ResourceScene : public Resource
{
public :
    ResourceScene(UID uid);
    ~ResourceScene();


	void Save()const;
	void Load()const;
	void UnLoad()const;
	GameObject GetRoot() const { return *root; };
	static void Load(std::shared_ptr<Resource>& resource, std::ifstream& data);
	//sotre all materials used by the obj
	vector<UID> materials;
	//sotre all meshes used by the obj
	vector<UID> meshes;
	GameObject* root;
};

