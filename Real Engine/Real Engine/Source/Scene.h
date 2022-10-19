#pragma once
#include "Module.h"
#include "GameObject.h"
#include <iostream>

struct mesh
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class Scene : public Module
{
public:


	 bool Awake();
	

	 bool Start();
	

	 bool PreUpdate();
	

	 bool Update(float dt);
	

	 bool PostUpdate();
	

	 bool CleanUp();
	
	 bool HandleEvent(Event* singleEvent);
	
	GameObject* CreateGameObject();
		
	list<GameObject*> gameObjects;

	//list<System*> systems;


	void LoadFile();
};

