#pragma once
#include "Component.h"
#include "ResourceMaterial.h"

//RESOUCE
struct  Material : public  Component
{
	std::shared_ptr<ResourceMaterial> resource;
};

