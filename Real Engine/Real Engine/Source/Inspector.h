#pragma once
#include "Panel.h"
#include "Events.h"
class Inspector : public Panel
{
public:
	Inspector(int _id,bool isActive);
	~Inspector();
	void Init();
	void Update();
	void DrawComponents(Entity entity);
	OnFOVChange fovChange;
	Entity context = -1;
};

