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
	std::shared_ptr<Resource> resource;
	virtual void OnUi() {}
};

struct MeshComponent : Component
{
	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam
};

struct TextureComponent : Component
{
	unsigned int Texture_ID;
};

struct MaterialComponent : Component
{
	unsigned int Shader_ID;
};

