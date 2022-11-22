#pragma once

#include "Module.h"
#include "System.h"
#include <iostream>
#include <map>
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
	
	UID Find(const char* file_in_assets) const;
	UID ImportFile(const char* new_file_in_assets);
	UID GenerateNewUID();

	const Resource* RequestResource(UID uid) const;
	Resource* RequestResource(UID uid);
	void ReleaseResource(UID uid);

private:
	Resource* CreateNewResource(const char* assetsFile, Resource::Type type);
	Resource::Type FilterFile(const char* file_path);
	std::map<UID, Resource*> resources;

};

