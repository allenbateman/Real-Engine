#pragma once
#include <iostream>
#include <list>
#include "SString.h"
#include "Component.h"

class Component;
enum componentType;

class GameObject
{
public:
	void Update();
	Component* CreateComponent(componentType type);
	
	bool active;
	SString name;
	std::list<Component*> components;


};
