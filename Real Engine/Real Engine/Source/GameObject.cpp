#include "GameObject.h"

GameObject::GameObject()
{
	id = app->entityComponentSystem.CreateEntity();
	name = "Game object";
	//app->entityComponentSystem.AddComponent(id, Transform{});
	//app->entityComponentSystem.AddComponent(id, TagComponent{ "Empty gameObject" });
}

GameObject::GameObject(std::string name)
{
	id = app->entityComponentSystem.CreateEntity();
	this->name = name;
	//app->entityComponentSystem.AddComponent(id, Transform{});
	//app->entityComponentSystem.AddComponent(id, TagComponent{ name });
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
