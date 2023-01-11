#pragma once
#include "Resource.h"
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
	~ResourceMesh();

	void Save()const;
	void Load();
	void UnLoad()const;

	static void Load(std::shared_ptr<Resource>& resource, std::ifstream& data);
	void LoadMetaData(std::ifstream& data) override;
	void GenerateMetaFile() override;
	unsigned int GetVAO() { return VAO; }

public:
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	UID material_UID;
	int materialIndex;
private:
	unsigned int VAO, VBO, EBO; // idex of the vertex array object in VRam
};

