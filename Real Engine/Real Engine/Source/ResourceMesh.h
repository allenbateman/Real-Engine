#pragma once
#include "Resource.h"
class ResourceMesh : public Resource
{
public:
	ResourceMesh(UID id);
	~ResourceMesh();

	void Save()const;
	void Load()const;
	void UnLoad()const;

	static  Resource* Load(std::string UUID, std::ifstream& data);
	int indices;
};

