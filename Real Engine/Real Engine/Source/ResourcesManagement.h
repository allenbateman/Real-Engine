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

	bool Init();

	bool Awake();
	bool Start();
	void HandleEvent(Event* e);
	void OnDrop(const std::string file_path);
	
	UID FindResource(const char* file_in_assets) const;
	UID ImportFile(const string assetsFile, Resource::Type type);

	shared_ptr<Resource> LoadResource(UID uid);
	shared_ptr<Resource> RequestResource(UID uid);
	void ReleaseResource(UID uid);

	shared_ptr<Resource> GetResource(UID uid);

	std::vector<filesystem::path> SearchForFileType(const std::filesystem::path root, const std::string extension);


	bool Exists(const std::filesystem::path& path)
	{
		ifstream ifile;
		ifile.open(path);
		if (ifile) {
			return true;
		}
		else {
			return false;
		}
	}
	//creates a new resource when needed
	shared_ptr<Resource> CreateNewResource(const std::filesystem::path assetsFile, Resource::Type type);
private:

	//loads the meta file and creates the resource
	void LoadMetaFile(shared_ptr<Resource>& resource, std::ifstream& metaFile);
	void ReImportAsset(shared_ptr<Resource>& resource);
	//shared_ptr<Resource> ImportResourceFromMetaFile(shared_ptr<Resource> resource);
	//Load all the meta files in the program, if a file is not in lib
	//it imports the file again
	void LoadMetaFiles();

	//Read all files from Assets folder and import if its not imported
	//Do this at the begining of the program and onFileChange, onDrop... any more?
	void ImportFilesFromAssets();

	//check if a file is already registered as a resource in a meta file
	bool ExistFileInResources(std::string filePath);

	//moves a on drop file to the assets folder	
	std::string MoveToAssets(const string diskPath);
	//generates a library file path for the imported file
	std::string GenLibraryPath(const string assetsFile);
	//filters the file through the supported files
	Resource::Type FilterFile(const char* filePath);

	//stores the link beteen UUID of imported resources with the resource it self
	std::map<UID,std::shared_ptr<Resource>> resources{};
};


