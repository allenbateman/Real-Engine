#pragma once
#include <iostream>
#include "ObjectLoader.h"
#include "GameObject.h"
#include "Transform.h"
class Scene
{
public:
	Scene();
	Scene(const char* name);
	~Scene();
	void Init();
	void Enable();
	void Disable();
	void CreateGameObject();
	void LoadGameObject(const std::string file_path);
	void RemoveEntity(Entity id);
	ObjectLoader objLoader;
	std::vector <GameObject> gameObejects;
	GameObject origin;
	//Scene properties
	unsigned int id;
	std::string name;
	//Transform origin;
};

