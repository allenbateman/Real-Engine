#pragma once
#include <iostream>
#include "Log.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
#include "Material.h"
class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	bool LoadObject(const char* file_path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void SetupMesh(const Mesh mesh);
	std::vector<Mesh> meshes;

};

