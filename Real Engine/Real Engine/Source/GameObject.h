#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Application.h"
#include "Entity.h"

class GameObject
{
public:
	GameObject();
	GameObject(std::string name);
	~GameObject();
	template<typename T>
	T& GetComponent();
	template<typename T>
	void AddComponent(T component);
	GameObject* FindChild(Entity id);
	void Destroy();


	bool active;
	Entity id = -1; // id of the game object
	std::string name;

};

template<typename T>
inline T& GameObject::GetComponent()
{
	return	app->entityComponentSystem.GetComponent<T>(id);
}

template<typename T>
inline void GameObject::AddComponent(T component)
{
	app->entityComponentSystem.AddComponent(id, component);
}
