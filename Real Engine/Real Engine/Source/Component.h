#pragma once
#include <iostream>
#include <bitset>
#include <cstdint>
#include <vector>
#include "glmath.h"
#include "Resource.h"

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

struct Component
{
	bool active;
	virtual void OnUi() {}
};