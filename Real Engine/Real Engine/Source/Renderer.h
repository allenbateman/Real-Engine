#pragma once
#include "Module.h"
class Renderer : public Module
{
public:
	Renderer(bool isActive);
	~Renderer();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

};

