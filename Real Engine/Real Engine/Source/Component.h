#pragma once
#include "glmath.h"
#include <iostream>
#include <vector>
 enum ComponentType
{
	DEFAULT = 0,
	MESH
};

struct Component
{
	ComponentType type;
	int id;
	bool active;

	virtual void Enable();
	virtual void Update();
	virtual void Disable();
};
