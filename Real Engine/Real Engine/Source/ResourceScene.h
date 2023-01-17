#pragma once
#include "Resource.h"
#include "GameObject.h"

#define MAX_CHILDS 100
class ResourceScene : public Resource
{
public :
    ResourceScene(UID uid);
    ResourceScene();
    ~ResourceScene();


	void SaveData();
	void LoadData();
	void Load();
	void UnLoad();
	GameObject GetRoot() const { return *root; };
private:
	nlohmann::json SaveNodeData(Transform& root);
	void LoadNodeData(nlohmann::json& node,GameObject* root);
public:

	//sotre all materials ids used by the obj
	vector<UID> materials;
	//sotre all meshes ids used by the obj
	vector<UID> meshes;
	mat4x4 transform;
	GameObject* root;
};