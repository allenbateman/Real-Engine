#pragma once
#include "Panel.h"
#include "Renderer.h"
class Viewport : public Panel
{
public:

	Viewport(int _id,bool isActive);
	~Viewport();
	void Init();
	void Update();
	bool CleanUp();
};