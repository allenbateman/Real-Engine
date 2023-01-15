#pragma once
#include "Resource.h"
#include "ResourceShader.h"
#include "ResourceMaterial.h"
#include "glmath.h"
struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
	vec4 Color;
};
class ResourceMesh : public Resource
{
public:
	ResourceMesh(UID id);
	ResourceMesh();
	~ResourceMesh();

	void SaveData();
	void LoadData();
	void Load();
	void UnLoad();
	unsigned int GetVAO() { return VAO; }
	void Draw(std::shared_ptr < ResourceShader> shader, std::shared_ptr < ResourceMaterial> material);
public:
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	UID material_UID;
	int materialIndex;
private:
	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam
};

