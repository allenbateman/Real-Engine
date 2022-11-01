#pragma once
#include "Module.h"
#include "System.h"
#include "ObjectLoader.h"
class SceneManager : public Module, public System
{
public:
	SceneManager() {};
	~SceneManager();

	bool Awake();
	bool Start();
	bool Updte();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();
	void HandleEvent(Event* e);

};

