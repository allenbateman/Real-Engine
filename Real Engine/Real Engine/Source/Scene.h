#pragma once
#include <iostream>
#include "ObjectLoader.h"
#include "GameObject.h"

class Scene
{
public:

	void Init();
	void Enable();
	void Disable();
	void CreateGameObject();
	void LoadGameObject(const std::string file_path);
	ObjectLoader objLoader;
	std::vector <GameObject> gameObejects;
	
	//Scene properties
	unsigned int id;
	std::string name;
};

