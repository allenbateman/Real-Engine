#pragma once
#include "Component.h"
#include "Shader.h"
#include "Material.h"

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
	vec4 Color;
};
class Mesh : public  Component
{
public:	
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;

	void Draw(Shader& shader ,Material& mat);
	//void Draw(Shader& Shader, Material& mat);
	unsigned int GetVAO() { return VAO; }
	unsigned int MatId;
private:
	void LoadMesh();
	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam

};

