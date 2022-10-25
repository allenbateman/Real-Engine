#pragma once
#include <iostream>
#include <bitset>
#include <cstdint>
#include <vector>
#include "glmath.h"
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

struct Component
{
	ComponentType type;
	int id;
	bool active;
};
