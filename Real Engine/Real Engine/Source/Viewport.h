#pragma once
#include "Panel.h"
#include "Application.h"
#include "Renderer.h"
class Viewport : public Panel
{
public:

	Viewport(bool isActive);
	~Viewport();
	bool Init();
	bool Update();
	bool PostUpdate();
	bool CleanUp();
};

