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

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

