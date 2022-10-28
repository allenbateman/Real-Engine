#pragma once
#include "Panel.h"
#include "Inspector.h"
class SceneHerarchyPanel :  public Panel
{
public:
	SceneHerarchyPanel(int _id, bool active);
	~SceneHerarchyPanel();
	void Init();
	void Update();
	void DrawEntityNode(Entity entity);
	Entity entitySelectionContext;
	Inspector* inspector;
};

