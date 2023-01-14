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
	vector<shared_ptr<Resource>> GetResourceListOfType(Resource::Type type);

	std::vector<filesystem::path> SearchForFileType(const std::filesystem::path root, const std::string extension);
	std::filesystem::path GetFilePath(string rootFolder,string filename);

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
	void RemoveResource(UID uid);
	//check if a file is already registered as a resource in a meta file
	bool ExistFileInResources(std::string filePath);

	std::multimap<string, std::pair<UID, std::shared_ptr<Resource>>> GetResourcesList() { return resources; };
private:

	//loads the meta file and creates the resource
	void LoadMetaFile(shared_ptr<Resource>& resource, std::ifstream& metaFile);

	//Load all the meta files in the program, if a file is not in lib
	//it imports the file again
	void LoadMetaFiles();

	//Read all files from Assets folder and import if its not imported
	//Do this at the begining of the program and onFileChange, onDrop... any more?
	void ImportFilesFromAssets();


	//moves a on drop file to the assets folder	
	std::string MoveToAssets(const string diskPath);
	//generates a library file path for the imported file
	std::string GenLibraryPath(const string assetsFile);
	//filters the file through the supported files
	Resource::Type FilterFile(const char* filePath);

	//stores the link beteen UUID of imported resources with the resource it self
	//std::map<UID,std::shared_ptr<Resource>> resources{};
	std::multimap<string, std::pair<UID, std::shared_ptr<Resource>>> resources{};
};


template<typename T>
class ResourceManager {
public:
	UID Add(const std::string& filePath)
	{
		auto it = resources.find(filePath);
		if (it == resources.end())
		{
			return it->second.first;
		}

		shared_ptr<T> resource = std::make_shared<T>();
	}
	void CreateResource(const std::string& filepath);
private:
	std::map<string, std::pair<UID, std::shared_ptr<T>>> resources{};
};

template<typename T>
inline void ResourceManager<T>::CreateResource(const std::string& filepath)
{
	//UID uid = uuid::generate_uuid();

	//switch (type) {
	//case Resource::Type::Texture: ret = shared_ptr<T>(new ResourceTexture(uid)); break;
	//case Resource::Type::Mesh: ret = shared_ptr<T>(new ResourceMesh(uid)); break;
	//case Resource::Type::Fbx: ret = shared_ptr<T>(new ResourceScene(uid)); break;
	//case Resource::Type::Material: ret = shared_ptr<T>(new ResourceMaterial(uid)); break;
	//case Resource::Type::UNKNOWN:return nullptr; break;
	//default: break;
	//}
	//if (ret != nullptr)
	//{
	//	ret->name = path.stem().string();
	//	ret->SetAssetPath(path.string());
	//	Debug::Log("Importing new asset:" + ret->name);
	//	resources.insert(std::make_pair(path.string(), std::make_pair(uid, ret)));
	//}
	//return ret;
}
