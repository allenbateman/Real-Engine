#pragma once
#include "Resource.h"
#include "GameObject.h"

#define MAX_CHILDS 100
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
	void Load(std::ifstream& data) override;
	//sotre all materials ids used by the obj
	vector<UID> materials;
	//sotre all meshes ids used by the obj
	vector<UID> meshes;
	//sotre all transforms used by the obj
	vector<UID> transforms;
	GameObject* root;
};

template<typename T>
class ComponentList
{
	vector<vector<T>> componentsList;
};
