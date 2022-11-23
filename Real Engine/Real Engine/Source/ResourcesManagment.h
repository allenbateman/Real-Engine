#pragma once

#include "Module.h"
#include "System.h"
#include <iostream>
#include <map>
#include "Entity.h"
#include "Resource.h"
#include "Importer.h"

//static const char* LibraryDir = "../Output/Library/";
class ResourcesManagment : public Module, public System
{
public:
	ResourcesManagment(bool isActive);
	~ResourcesManagment();

	bool Awake();
	bool Start();
	void HandleEvent(Event* e);
	void OnDrop(const std::string file_path);
	
	UID Find(const char* file_in_assets) const;
	UID ImportFile(const string assetsFile, Resource::Type type);
	UID GenerateNewUID();

	const Resource* RequestResource(UID uid) const;
	Resource* RequestResource(UID uid);
	void ReleaseResource(UID uid);

private:
	Resource* CreateNewResource(const string assetsFile, Resource::Type type);
	std::string MoveToAssets(const string diskPath);
	std::string GenerateLibraryPath(const string assetsFile);
	Resource::Type FilterFile(const char* file_path);
	std::map<UID, Resource*> resources{};

};

