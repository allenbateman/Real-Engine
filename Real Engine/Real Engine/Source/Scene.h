#pragma once
#include "Module.h"
#include "GameObject.h"

class Scene
{
public:
	GameObject* CreateGameObject();
		
	list<GameObject*> gameObjects;

};

