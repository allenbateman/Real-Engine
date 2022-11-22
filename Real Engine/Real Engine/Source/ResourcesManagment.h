#pragma once

#include "Module.h"
#include "System.h"
#include <iostream>
#include <unordered_map>
#include "Entity.h"
#include "Resource.h"

struct LoadedFile {
	std::string name;
	unsigned int id;
};

class ResourcesManagment : public Module, public System
{
public:
	ResourcesManagment();
	~ResourcesManagment();
	
	//Subscribe entity to mesh
	int SubscribeEntityToMesh(const char* file_name, Entity ent);
	//Get a loaded mesh ID (VAO) id
	int  GetLoadedMesh(const char* file_name);
	//load mesh
	bool AddLoadedMesh(const char* file_name, unsigned int id);

private:
	//Mesh to entity
	std::unordered_map<unsigned int, std::vector<Entity>> subscribedMesh{};
	//Filename to loaded id
	std::unordered_map<const char*, unsigned int> loadedMesh{};

};

