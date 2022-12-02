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

	int indices;
};

