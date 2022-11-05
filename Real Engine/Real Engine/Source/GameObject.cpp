#include "GameObject.h"
#include "Tag.h"
#include "Transform.h"


GameObject::GameObject()
{
	id = app->entityComponentSystem.CreateEntity();
	name = "Game object";
	app->entityComponentSystem.AddComponent(id, Transform{});
	app->entityComponentSystem.AddComponent(id, TagComponent{ "Empty gameObject" });
	active = true;
}

GameObject::GameObject(std::string name)
{
	id = app->entityComponentSystem.CreateEntity();
	app->entityComponentSystem.AddComponent(id, Transform{});
	app->entityComponentSystem.AddComponent(id, TagComponent{ name });
	this->name = name;
	active = true;
}

GameObject::~GameObject()
{
}

GameObject* GameObject::FindChild(Entity id)
{
	//for (auto& child : childs)
	//{
	//	if (child->id == id)
	//		return child; 
	//}

	return nullptr;
}

void GameObject::Destroy()
{
	//if has childs destroy them too
	app->entityComponentSystem.DestroyEntity(id);
}
