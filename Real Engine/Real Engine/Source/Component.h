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
	UID resource_id;
	virtual void OnUi() {}
};
//
//struct MeshComponent : Component
//{
//	UID resource_id;
//	shared_ptr<Resource> resource;
//	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam
//};
//
//struct TextureComponent : Component
//{
//	UID resource_id;
//	shared_ptr<Resource> resource;
//};
//
//struct CameraComponent : Component
//{
//	UID resource_id;
//	shared_ptr<Resource> resource;
//};
//
