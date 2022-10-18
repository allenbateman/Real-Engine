#pragma once
#include <iostream>
#include <list>
#include "Component.h"
#include "SString.h"



class GameObject
{
	public:
	void Update();
	Component* CreateComponent(componentType type);

	bool active;
	SString name;
	std::list<Component*> components;
	
	
};

