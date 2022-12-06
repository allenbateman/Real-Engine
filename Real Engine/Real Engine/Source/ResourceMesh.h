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

	static  Resource* Load(Resource* resource, std::ifstream& data);
	int indices;
};

