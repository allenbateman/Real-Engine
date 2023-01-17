#include "GameObject.h"
#include "Tag.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"


GameObject::GameObject()
{
	id = app->entityComponentSystem.CreateEntity();
	name = "Game object";
	Transform t;
	t.owner = this;
	AddComponent( t);
	AddComponent( TagComponent{ "Empty gameObject" });
	active = true;

}

GameObject::GameObject(std::string name)
{
	id = app->entityComponentSystem.CreateEntity();
	cout << "Creating Entity " + name <<endl;
	Transform t;
	t.owner = this;
	AddComponent( t);
	AddComponent(TagComponent{ name });
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
		else
			return child->owner->FindChild(toFind);
	}

	return nullptr;
}

GameObject* GameObject::FindChildByName(const std::string toFind)
{
	vector<Transform*> childs = GetComponent<Transform>().childs;
	for (auto& child : childs)
	{
		if (child->owner->GetComponent<TagComponent>() == toFind)
			return child->owner;
		else
			return child->owner->FindChild(toFind);
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
	//now remove all the components

	if (HasComponent<Mesh>())
	{
		Mesh m = GetComponent<Mesh>();
		m.resource.reset();
	}
	if (HasComponent<Material>())
	{
		Material m = GetComponent<Material>();
		m.resource.reset();
	}
	// remove entity from ECS
	app->entityComponentSystem.DestroyEntity(id);
	//destroy go
	this->~GameObject();
}

void GameObject::Save()
{
}
