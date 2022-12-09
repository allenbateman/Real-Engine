#pragma once
#include "Resource.h"
#include "Mesh.h"
class ResourceMesh : public Resource
{
public:
	ResourceMesh(UID id);
	~ResourceMesh();

	void Save()const;
	void Load()const;
	void UnLoad()const;

	static std::shared_ptr<Resource> Load(std::shared_ptr<Resource> resource, std::ifstream& data);
	int materialIndex;
};

