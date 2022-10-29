#pragma once
#include "Component.h"
#include "Shader.h"
#include "Material.h"

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};
class Mesh
{
public:
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();
	void Draw(Shader& shader ,Material& mat);
	//void Draw(Shader& Shader, Material& mat);
	unsigned int GetVAO() { return VAO; }
	unsigned int MatId;
private:
	void SetupMesh();
	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam

};

