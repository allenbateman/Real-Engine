#pragma once
#include "Component.h"
#include "glmath.h"
#include <iostream>
#include <vector>
struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};
struct Texture {
	unsigned int id;
	std::string type;
};
class Mesh : public Component
{


public:
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;
	
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();
private:
	void SetupMesh();
	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam
};

