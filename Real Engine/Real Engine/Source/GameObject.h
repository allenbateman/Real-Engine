#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Application.h"
#include "Entity.h"

struct Transform;

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
	GameObject* FindChild(const GameObject toFind);
	GameObject* FindChild(const Entity toFind);
	void RemoveChild(Entity childToRemove);

	void Destroy();


	bool active;
	Entity id = -1; // id of the game object
	std::string name;


	bool operator != (GameObject other)
	{
		return (id != other.id);
	}

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
