#pragma once
#include <iostream>
#include "ObjectLoader.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObjectTypes.h"

class Scene
{
public:
	Scene();
	Scene(const char* name);
	~Scene();
	void Init();
	void Enable();
	void Disable();
	void CreateGameObject(gameObjectType goType);
	void LoadGameObject(const std::string file_path);
	void RemoveEntity(Entity id);
	std::vector <GameObject> gameObejects;
	GameObject origin;
	//Scene properties
	unsigned int id;
	std::string name;
	//Transform origin;
};

