#pragma once
#include "Component.h"
#include "Texture.h"


class Material
{
public:
	Material();
	Material(std::vector<Texture>& texture);
	~Material();
	//sotres all texture maps diffuse,roughness etc
	std::vector<Texture> textures;

	std::vector < Texture> diffuse;
	std::vector < Texture> ambient;
	std::vector < Texture> specular;
	float shininess;
};

