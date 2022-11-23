#include "ResourcesManagment.h"
#include <filesystem>
#include "EventSystem.h"
#include "Events.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "MD5.h"

ResourcesManagment::ResourcesManagment(bool isActive) : Module(isActive)
{
}

ResourcesManagment::~ResourcesManagment()
{
}

bool ResourcesManagment::Awake()
{
    return false;
}

bool ResourcesManagment::Start()
{
    app->eventSystem->SubscribeModule(this, ON_FILE_DROP);
    return true;
}

void ResourcesManagment::HandleEvent(Event* e)
{
    switch (e->type)
    {
    case ON_FILE_DROP:
    {
        OnFileDrop* drop = dynamic_cast<OnFileDrop*>(e);
        OnDrop(drop->path);
    }
    break;
    default:
        break;
    }

}

void ResourcesManagment::OnDrop(const std::string file_path)
{
    Resource::Type newFileType;
    newFileType = FilterFile(file_path.c_str());
    if (newFileType == Resource::Type::UNKNOWN)
        return;

    //once the file is something that we accept
    // move file from disk to the assets lib  
    std::size_t from = file_path.find_last_of('/\\');
    std::size_t to = file_path.find_last_of('.');
    std::string fileName = file_path.substr(from + 1, ' ');
    std::string newPathFolder = "../Output/Assets/";
    std::string newPath = newPathFolder + fileName;

    //store new file to assets
    if (rename(file_path.c_str(), newPath.c_str()))
    {
        cout << "Could not move file: " << fileName << endl;
        return;
    }
    else
    {
        cout << "File moved from: " << file_path << "\n to \n" << newPath.c_str() << endl;
    }
    //Import the file
    
    ImportFile(file_path.c_str(), newFileType);
}

UID ResourcesManagment::Find(const char* file_in_assets) const
{

   
    return UID();
}

UID ResourcesManagment::ImportFile(const string new_file_in_assets, Resource::Type type)
{
    Resource* resource =  CreateNewResource(new_file_in_assets, type);


	return UID();
}

UID ResourcesManagment::GenerateNewUID()
{

    return UID();
}

const Resource* ResourcesManagment::RequestResource(UID uid) const
{
    return nullptr;
}

Resource* ResourcesManagment::RequestResource(UID uid)
{
    return nullptr;
}

void ResourcesManagment::ReleaseResource(UID uid)
{
}

Resource* ResourcesManagment::CreateNewResource(const string assetsFile, Resource::Type type)
{

    Resource* ret = nullptr;
    UID uid = md5(assetsFile);
    switch (type) {
//    case Resource::Type::Texture: ret = (Resource*) new ResourceTexture(uid); break;
//    case Resource::Type::Mesh: ret = (Resource*) new ResourceMesh(uid); break;
   /* case Resource::Type: ret = (Resource*) new ResourceScene(uid); break;
    case Resource::Type: ret = (Resource*) new ResourceBone(uid); break;
    case Resource::Type: ret = (Resource*) new ResourceAnimation(uid); break;*/
    default: break;
    }
    if (ret != nullptr)
    {
        //resources
        //resources[uid] = ret;
        //resources[uid]->assetsFile = assetsPath;
        //resource->libraryFile = GenLibraryPath(resource);
    }
    return ret;


    return nullptr;
}

std::string ResourcesManagment::GenerateLibraryPath(const string assetsFile)
{
    return std::string();
}

Resource::Type ResourcesManagment::FilterFile(const char* file_path)
{
        std::filesystem::path filePath = file_path;
        Resource::Type type = Resource::Type::UNKNOWN;
        if (filePath.extension() == ".fbx") // Heed the dot.
        {
            std::cout << filePath.stem() << " is a valid type.\n";
            type = Resource::Type::Fbx;
        }
        else if (filePath.extension() == ".dds")
        {
            std::cout << filePath.stem() << " is a valid type.\n";
        }
        else if (filePath.extension() == ".png")
        {
            std::cout << filePath.stem() << " is a valid type.\n";
        }
        return type;
}
