#pragma once
#include "Entity.h"
#include <set>

class System
{
public:
	std::set<Entity> entities;
};