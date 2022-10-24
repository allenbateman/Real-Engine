#pragma once
#include "glmath.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <cstdint>

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

struct Component
{
	ComponentType type;
	int id;
	bool active;

	virtual void Enable();
	virtual void Update();
	virtual void Disable();
};
