#pragma once
#include "Module.h"
#include "ObjectLoader.h"
class SceneManager : public Module
{
	SceneManager(bool isActive);
	~SceneManager();

	bool Awake();
	bool Start();
	bool Updte();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();
	void HandleEvent(Event* e);

};

