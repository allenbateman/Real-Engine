#include "GameObject.h"
#include "Tag.h"
#include "Transform.h"


GameObject::GameObject()
{
	id = app->entityComponentSystem.CreateEntity();
	name = "Game object";
	Transform t;
	t.owner = this;
	app->entityComponentSystem.AddComponent(id, t);
	app->entityComponentSystem.AddComponent(id, TagComponent{ "Empty gameObject" });
	active = true;

}

GameObject::GameObject(std::string name)
{
	id = app->entityComponentSystem.CreateEntity();
	Transform t;
	t.owner = this;
	app->entityComponentSystem.AddComponent(id, t);
	app->entityComponentSystem.AddComponent(id, TagComponent{ name });
	this->name = name;
	active = true;
}

GameObject::~GameObject()
{
}

GameObject* GameObject::FindChild(const GameObject toFind)
{
	vector<Transform*> childs = GetComponent<Transform>().childs;
	for (auto& child : childs )
	{
		if (child->owner->id == toFind.id)
			return child->owner; 
	}

	return nullptr;
}

GameObject* GameObject::FindChild(const Entity toFind)
{
	vector<Transform*> childs = GetComponent<Transform>().childs;
	for (auto& child : childs)
	{
		if (child->owner->id == toFind)
			return child->owner;
	}

	return nullptr;
}

void GameObject::Destroy()
{
	//if has childs destroy them too
	vector<Transform*> childs = GetComponent<Transform>().childs;
	for (auto& child : childs)
	{
		child->owner->Destroy();
	}

	//remove go from its parent child list
	Transform* tParent = GetComponent<Transform>().parent;
	tParent->RemoveChild(GetComponent<Transform>());

	// remove entity from ECS
	app->entityComponentSystem.DestroyEntity(id);
	//destroy go
	this->~GameObject();
}
