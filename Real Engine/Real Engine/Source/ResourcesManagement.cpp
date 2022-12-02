#include "ResourcesManagement.h"
#include <filesystem>
#include "EventSystem.h"
#include "Events.h"
#include "UiSystem.h"
#include "UUID.h"


#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ResourceFbx.h"


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
  
    return true;
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
    {
        Debug::Warning("We dont support that file Type :(");
        return;
    }

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

    if (resource == nullptr)
        return "";
    
    switch (resource->GetType())
    {
    case Resource::Type::Fbx: ImportFbx(assets_path); break;
    case Resource::Type::Texture: 
        TextureImporter::Import(resource); 
        break;
    default:
        break;
    }

    resource->Save();

	return resource->GetID();
}

Resource* ResourcesManagement::LoadResource(UID uid)
{
    std::map<UID, Resource*>::iterator it = resources.begin();
    if (it != resources.end())
    {
        it->second->Load();
        it->second->IncreaseReferenceCount();
        return nullptr;
    }
    return nullptr;
}

const Resource* ResourcesManagement::RequestResource(UID uid) const
{
    ////Find if the resource is already loaded
    //std::map<UID, Resource*>::iterator it = resources.begin();
    //if (it != resources.end())
    //{
    //    it->second->IncreaseReferenceCount();
    //    return it->second;
    //}
    ////Find the library file (if exists) and load the custom file format
    //return LoadResource(uid);
    return nullptr;
}

void ResourcesManagement::ReleaseResource(UID uid)
{
    resources.erase(uid);
}

void ResourcesManagement::ImportFilesFromAssets()
{
    filesystem::path entry = ASSETS_DIR;
    filesystem::directory_iterator currentDir;
    
    cout << "Reading Assets folder \n";
    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{ entry })
    {
        if (!dir_entry.exists()) return;
        if (dir_entry.is_directory())
        {
            std::cout << dir_entry << '\n';
            continue;
        }
        else {
            std::cout <<'\t' << dir_entry << '\n';
            Resource::Type type =  FilterFile(dir_entry.path().string().c_str());
            ImportFile(dir_entry.path().string().c_str(), type);
        }
    }
}

UID ResourcesManagement::GenerateUID()
{
    return "asd";
}

Resource* ResourcesManagement::CreateNewResource(const string assets_path, Resource::Type type)
{

    Resource* ret = nullptr;
    UID uid = uuid::generate_uuid();


    std::size_t from = assets_path.find_last_of('/');
    std::string fileName = assets_path.substr(from + 1, ' ');

    switch (type) {
    case Resource::Type::Texture: ret = (Resource*) new ResourceTexture(uid);break;
    case Resource::Type::Mesh: ret = (Resource*) new ResourceMesh(uid); break;
    case Resource::Type::Fbx: ret = (Resource*) new ResourceFbx(uid); break;
    case Resource::Type::UNKNOWN:return nullptr; break;
    default: break;
    }
    if (ret != nullptr)
    {
        resources[uid] = ret;
        ret->SetType(type);
        ret->SetAssetPath(assets_path);
        ret->SetLibraryPath(GenLibraryPath(assets_path));
        Debug::Log("Importing asset:" + fileName);
        Debug::Log(" id:" + uid);
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
    return *newPath;
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
        type = Resource::Type::Texture;
    }
    else if (filePath.extension() == ".png")
    {
        std::cout << filePath.stem() << " is a valid type.\n";
        type = Resource::Type::Texture;
    }
    else if (filePath.extension() == ".jpg")
    {
        std::cout << filePath.stem() << " is a valid type.\n";
        type = Resource::Type::Texture;
    }
    else {
        std::cout << "unknown file type";
        type = Resource::Type::UNKNOWN;
    }
    return type;
}

void ResourcesManagement::ImportFbx(const std::string& file_path)
{
    //create
    const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

    if (scene != nullptr && scene->HasMeshes())
    {
        app->importer->directory = file_path.substr(0, file_path.find_last_of('/'));

        std::size_t from = file_path.find_last_of('/');
        std::size_t to = file_path.find_last_of('.');
        std::string fbxName = file_path.substr(from + 1, to);
        fbxName = fbxName.substr(0, fbxName.find_last_of('.'));
        vector<Mesh> meshes;
        FbxImporter::ProcessNode(scene->mRootNode, scene, &meshes);
        aiReleaseImport(scene);

    }
    else
    {
        std::cout << aiGetErrorString();
        LOG(aiGetErrorString());
    }
    
}
