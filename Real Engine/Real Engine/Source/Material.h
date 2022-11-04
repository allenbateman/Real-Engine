#pragma once
#include "Component.h"
#include "Texture.h"


class Material : public  Component
{
public:
	Material();
	Material(std::vector<Texture>& texture);
	~Material();
	//sotres all texture maps diffuse,roughness etc
	std::vector<Texture> textures;
};

