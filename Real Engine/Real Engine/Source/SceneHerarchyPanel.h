#pragma once
#include "Panel.h"
#include "Inspector.h"
class GameObject;
class SceneHerarchyPanel :  public Panel
{
public:
	SceneHerarchyPanel(int _id, bool active);
	~SceneHerarchyPanel();
	void Init();
	void Update();
	void DrawGONode(GameObject go);
	Entity entitySelectionContext;
	Inspector* inspector;
	bool DeletedEntity = false;
	Entity toDelete;

private:
	
};
static const char* payloadDragDrop = "SceneHierarchy";
