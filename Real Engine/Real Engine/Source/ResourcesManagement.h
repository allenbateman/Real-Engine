#pragma once
#include "Module.h"
#include "System.h"
#include <iostream>
#include <map>
#include "Entity.h"
#include "Resource.h"
#include "Importer.h"

class ResourcesManagement : public Module
{
public:
	ResourcesManagement(bool isActive);
	ResourcesManagement();
	~ResourcesManagement();

	bool Awake();
	bool Start();
	void HandleEvent(Event* e);
	void OnDrop(const std::string file_path);
	
	UID Find(const char* file_in_assets) const;
	UID ImportFile(const string assetsFile, Resource::Type type);

	Resource* LoadResource(UID uid);
	const Resource* RequestResource(UID uid) const;
	void ReleaseResource(UID uid);

	//Read all files from Assets folder and import if its not imported
	//Do this at the begining of the program and onFileChange, onDrop... any more?
	void ImportFilesFromAssets();
	UID GenerateUID();
private:
	Resource* CreateNewResource(const string assetsFile, Resource::Type type);
	std::string* MoveToAssets(const string diskPath);
	std::string GenLibraryPath(const string assetsFile);
	Resource::Type FilterFile(const char* file_path);
	std::map<UID, Resource*> resources{};

};
