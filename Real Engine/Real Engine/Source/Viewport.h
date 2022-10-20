#pragma once
#include "Panel.h"
#include "Renderer.h"
class Viewport : public Panel
{
public:

	Viewport(int _id,bool isActive);
	~Viewport();
	bool Init();
	bool Update();
	bool PostUpdate();
	bool CleanUp();
};

