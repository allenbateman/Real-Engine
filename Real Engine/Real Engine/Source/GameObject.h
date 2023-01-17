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

	GameObject* FindChild(const GameObject toFind);
	GameObject* FindChild(const Entity toFind);
	GameObject* FindChildByName(const std::string toFind);
	void RemoveChild(Entity childToRemove);
	void Destroy();

	template<typename T>
	bool HasComponent();
	template<typename T>
	T& GetComponent();
	template<typename T>
	void AddComponent(T component);

	void Save();
	//std::vector<Component> components;
	unsigned int childsCount = 0;
	vector<unsigned int> meshIndex;//array of indices to the mesh used
	unsigned int meshCount;//number of meshes used by the node

	bool active;
	Entity id = -1; // id of the game object
	std::string name;


	bool operator != (GameObject other)
	{
		return (id != other.id);
	}
	bool operator == (GameObject other)
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

template<typename T>
inline bool GameObject::HasComponent()
{
	return	app->entityComponentSystem.HasComponent<T>(id);
}
