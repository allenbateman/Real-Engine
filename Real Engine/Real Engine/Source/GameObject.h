#pragma once
#include <iostream>
#include <list>
#include <string>

#include "Application.h"
#include "Entity.h"

class GameObject
{
public:
	GameObject();
	GameObject(std::string name);
	~GameObject();
	bool active;
	Entity id = -1; // id of the game object
	std::string name;
	GameObject* parent;
	std::vector<GameObject*> childs;

	template<typename T>
	T& GetComponent();

	template<typename T>
	void AddComponent(T component);

	GameObject* FindChild(Entity id);

	void Destroy();
};

template<typename T>
inline T& GameObject::GetComponent()
{
	app->entityComponentSystem.GetComponent<T>(id);
}

template<typename T>
inline void GameObject::AddComponent(T component)
{
	app->entityComponentSystem.AddComponent(id, component);
}
