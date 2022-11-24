#include "ResourcesManagement.h"
#include <filesystem>
#include "EventSystem.h"
#include "Events.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ResourceFbx.h"
#include "MD5.h"
#include "UiSystem.h"

ResourcesManagement::ResourcesManagement(bool isActive) : Module(isActive)
{
}

ResourcesManagement::ResourcesManagement()
{
}

ResourcesManagement::~ResourcesManagement()
{
}

bool ResourcesManagement::Awake()
{
    return false;
}

bool ResourcesManagement::Start()
{
    app->eventSystem->SubscribeModule(this, ON_FILE_DROP);
    return true;
}

void ResourcesManagement::HandleEvent(Event* e)
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

void ResourcesManagement::OnDrop(const std::string file_path)
{
    Resource::Type newFileType;
    newFileType = FilterFile(file_path.c_str());
    if (newFileType == Resource::Type::UNKNOWN)
        return;

    std::string* assets_path =  MoveToAssets(file_path);

    if (assets_path == nullptr)
        return;

    //Import the file
    
    ImportFile(assets_path->c_str(), newFileType);
}

UID ResourcesManagement::Find(const char* file_in_assets) const
{

   
    return UID();
}

UID ResourcesManagement::ImportFile(const string assets_path, Resource::Type type)
{
    Resource* resource =  CreateNewResource(assets_path, type);


	return resource->GetID();
}

const Resource* ResourcesManagement::RequestResource(UID uid) const
{
    return nullptr;
}

Resource* ResourcesManagement::RequestResource(UID uid)
{
    return nullptr;
}

void ResourcesManagement::ReleaseResource(UID uid)
{
}

Resource* ResourcesManagement::CreateNewResource(const string assets_path, Resource::Type type)
{

    Resource* ret = nullptr;
    UID uid = md5(assets_path);
    switch (type) {
    case Resource::Type::Texture: ret = (Resource*) new ResourceTexture(uid); break;
    case Resource::Type::Mesh: ret = (Resource*) new ResourceMesh(uid); break;
    case Resource::Type::Fbx: ret = (Resource*) new ResourceFbx(uid); break;
    //case Resource::Type::Scene: ret = (Resource*) new ResourceBone(uid); break;
    //case Resource::Type::Shader: ret = (Resource*) new ResourceAnimation(uid); break;
    default: break;
    }
    if (ret != nullptr)
    {
        resources[uid] = ret;
        resources[uid]->SetAssetPath(assets_path);
        resources[uid]->SetLibraryPath(GenLibraryPath(assets_path));
    }
    return ret;
}

std::string* ResourcesManagement::MoveToAssets(const string disc_path)
{
    //once the file is something that we accept
    // move file from disk to the assets lib  
    std::size_t from = disc_path.find_last_of('/\\');
    std::string fileName = disc_path.substr(from + 1, ' ');
    std::string newPathFolder = "../Output/Assets/";
    std::string* newPath = new std::string(newPathFolder + fileName);

    //store new file to assets
    if (rename(disc_path.c_str(), newPath->c_str()))
    {
        Debug::Warning("Couldn't load file: " + fileName);
        return nullptr;
    }
    else
    {
        Debug::Log("File moved to assets: " + fileName);
        return newPath;
    }

}

std::string ResourcesManagement::GenLibraryPath(const string assets_path)
{
    //once the file is in assets 
    // move file from assets to the lib  
    std::size_t from = assets_path.find_last_of('/');
    std::string fileName = assets_path.substr(from + 1, ' ');
    std::string newPathFolder = "../Output/Library/";
    std::string* newPath = new std::string(newPathFolder + fileName);
    //store new file to assets
    if (rename(assets_path.c_str(), newPath->c_str()))
    {
        Debug::Warning("Couldn't load file: " + fileName);
        return nullptr;
    }
    else
    {
        Debug::Log("File imported to library: " + fileName);
        return *newPath;
    }
}

Resource::Type ResourcesManagement::FilterFile(const char* file_path)
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
