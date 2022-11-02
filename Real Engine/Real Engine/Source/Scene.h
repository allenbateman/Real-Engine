#pragma once
#include "Module.h"
#include "Application.h"
#include <iostream>
#include "Entity.h"

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

	Entity entitySelectionContext;
};

