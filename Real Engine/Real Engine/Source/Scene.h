#pragma once
#include "Module.h"
#include "Application.h"
#include <iostream>
#include "GameObject.h"
#include "ObjectLoader.h"
class Scene
{
public:


	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void HandleEvent(Event* singleEvent);

	void CreateGameObject();
	std::vector <GameObject> gameObejects;
	ObjectLoader objLoader;
};

