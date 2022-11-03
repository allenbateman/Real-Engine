#include "GameObject.h"

GameObject::GameObject()
{
	id = app->entityComponentSystem.CreateEntity();
	AddComponent(TagComponent{});
	AddComponent(Transform{});
	name = "Game object";
}

GameObject::GameObject(std::string name)
{
	id = app->entityComponentSystem.CreateEntity();
	AddComponent(TagComponent{ name });
	AddComponent(Transform{});
	this->name = name;
}

GameObject::~GameObject()
{
}

GameObject* GameObject::FindChild(Entity id)
{
	for (auto& child : childs)
	{
		if (child->id == id)
			return child; 
	}

	return nullptr;
}

void GameObject::Destroy()
{
	//if has childs destroy them too
	app->entityComponentSystem.DestroyEntity(id);
}
