#pragma once
#include <iostream>
#include <list>
#include "SString.h"
#include "Component.h"

class GameObject
{
public:
	void Update();
	void Destroy();	
	int id;
	bool active;
	SString name;
	std::list<Component*> components;
};
