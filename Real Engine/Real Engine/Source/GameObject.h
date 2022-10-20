#pragma once
#include <iostream>
#include <list>
#include "SString.h"
#include "Component.h"

class Component;
enum ComponentType;

class GameObject
{
public:
	void Update();
	void Destroy();
	Component* CreateComponent(ComponentType type);
	
	int id;
	bool active;
	SString name;
	std::list<Component*> components;
};
