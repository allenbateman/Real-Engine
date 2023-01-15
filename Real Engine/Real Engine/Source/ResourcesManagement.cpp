#include "ResourcesManagement.h"
#include <filesystem>
#include "EventSystem.h"
#include "Events.h"
#include "UiSystem.h"
#include "UUID.h"


#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ResourceScene.h"


ResourcesManagement::ResourcesManagement(bool isActive) : Module(isActive)
{
}

ResourcesManagement::ResourcesManagement()
{
}

ResourcesManagement::~ResourcesManagement()
{
}

bool ResourcesManagement::Init()
{

    bool ret = false;

    // create all resources from meta files 
    // read all meta files data 
    LoadMetaFiles();
    ImportFilesFromAssets();

    return ret;
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

    auto assets_path =  MoveToAssets(file_path);

    if (assets_path == "")
        return;

    //Import the file    
    ImportFile(assets_path.c_str(), newFileType);
}

UID ResourcesManagement::FindResource(const char* file_in_assets) const
{
    for (const auto& resource : resources)
    {
        if (strcmp(file_in_assets, resource.second.second->GetAssetPath().string().c_str()) == 0)
        {
            return resource.second.first;
        }
    }
   
    return "";
}

UID ResourcesManagement::ImportFile(const string assets_path, Resource::Type type)
{
    shared_ptr<Resource> resource =  CreateNewResource(assets_path, type);

    if (resource == nullptr)
        return "";
    
    switch (resource->GetType())
    {
    case Resource::Type::Fbx: SceneImporter::Import(resource); break;
    case Resource::Type::Texture: TextureImporter::Import(resource);break;
    case Resource::Type::Shader: ShaderImporter::Import(resource);break;
    default:
        break;
    }

    if (resource == nullptr)
        return "";

    resource->GenerateMetaFile(resource->GetAssetPath().string() + ".meta");
    resource->SaveData();

    UID ret = resource->GetID();
	return ret;
}

shared_ptr<Resource> ResourcesManagement::RequestResource(UID uid)
{
    std::map<string, pair<UID, shared_ptr<Resource>>>::iterator it = resources.begin();
    if (it != resources.end())
    {
        if (it->second.second->GetRefereneCount() <= 0)
        {
            it->second.second->Load();
        }
        return it->second.second;
    }
    return nullptr;
}

void ResourcesManagement::ReleaseResource(UID uid)
{
    resources.erase(uid);
}

shared_ptr<Resource> ResourcesManagement::GetResource(UID uid)
{
    std::map<string,pair<UID, shared_ptr<Resource>>>::iterator it = resources.begin();
    while (it != resources.end())
    {
        if (it->second.first == uid)
            return it->second.second;
        it++;
    }
    return nullptr;
}

vector<shared_ptr<Resource>> ResourcesManagement::GetResourceListOfType(Resource::Type type)
{
    vector< shared_ptr<Resource>> resourcesFound;

    std::map<string, pair<UID, shared_ptr<Resource>>>::iterator it = resources.begin();
    while (it != resources.end())
    {
        if (it->second.second->GetType() == type)
            resourcesFound.push_back(it->second.second);
        it++;
    }


    return resourcesFound;
}

std::vector<fs::path> ResourcesManagement::SearchForFileType(const std::filesystem::path root, const std::string extension)
{
    std::vector<fs::path> paths;
    if (filesystem::exists(root) && filesystem::is_directory(root))
    {
        for (auto const& entry : filesystem::recursive_directory_iterator(root))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == extension)
                paths.emplace_back(entry.path());
        }
    }
    return paths;
}

std::filesystem::path ResourcesManagement::GetFilePath(string rootFolder,string filename)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootFolder)) {
        if (entry.is_regular_file() && entry.path().filename().string() == filename) {
            return entry.path();
        }
    }
    return std::filesystem::path();
}

void ResourcesManagement::ImportFilesFromAssets()
{
    filesystem::path entry = ASSETS_DIR;
    //import files from assets that have not been imported yet
    vector <std::pair<filesystem::path, Resource::Type>> filesToLoad;
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
            bool exist = true;
            Resource::Type type = FilterFile(dir_entry.path().string().c_str());

            if (type != Resource::Type::UNKNOWN)
            {
              exist = ExistFileInResources(dir_entry.path().string());
            }
           
            if (!exist)
            {
               pair<filesystem::path, Resource::Type> p;
               p.first = dir_entry.path();
               p.second = type;                    
               filesToLoad.push_back(p);              
            }  
        }
    }

    //import files that have been left to add
    for (const auto& fileToLoad : filesToLoad)
    {

        if (!ExistFileInResources(fileToLoad.first.string()));
        {   
            ImportFile(fileToLoad.first.string().c_str(), fileToLoad.second); 
        }
    }
}

bool ResourcesManagement::ExistFileInResources(std::string filePath)
{
    for (const auto& resource : resources)
    {
        if (filePath == resource.first)
        {
            //file registered
            return  true;
        }
    }
    return false;
}

shared_ptr<Resource> ResourcesManagement::LoadMetaFile(std::string metaFile)
{
    shared_ptr<Resource> resource(new Resource(metaFile));

    //check that id file is stored in the project library
    // meaning we have the custom file 
    //if not load new resource 
    if (std::filesystem::exists(resource->GetLibraryPath()))
    {
        Debug::Log("Loading asset: " + resource->name);

        switch (resource->GetType()) {
        case Resource::Type::Texture:
        {
            shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceTexture());
            *ret = *resource;
            ret->LoadData();
            resources.insert(std::make_pair(ret->GetAssetPath().string(), std::make_pair(ret->GetID(), ret)));
        }break;
        case Resource::Type::Mesh: {
            shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceMesh());
            *ret = *resource;
            ret->LoadData();
            resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            return ret;
        }break;
        case Resource::Type::Fbx: {
            shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceScene());
            *ret = *resource;
            ret->LoadData();
            resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            return ret;
        }break;
        case Resource::Type::Material: {
            shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceMaterial());
            *ret = *resource;
            ret->LoadData();
            resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            return ret;
        }break;
        case Resource::Type::Shader: {
            shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceShader());
            *ret = *resource;
            ret->LoadData();
            resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            return ret;
        }break;
        case Resource::Type::UNKNOWN:     return nullptr; break;
        default:return nullptr; break;
        }
    }
    else {
        return nullptr;
    }
}

void ResourcesManagement::AddResource(shared_ptr<Resource>& resource)
{
    resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
}


shared_ptr<Resource> ResourcesManagement::CreateNewResource(const std::filesystem::path path, Resource::Type type)
{
    shared_ptr<Resource> ret;
    UID uid = uuid::generate_uuid();

    switch (type) {
    case Resource::Type::Texture: ret = shared_ptr<Resource>(new ResourceTexture(uid));break;
    case Resource::Type::Mesh: ret = shared_ptr<Resource>(new ResourceMesh(uid)); break;
    case Resource::Type::Fbx: ret = shared_ptr<Resource>(new ResourceScene(uid)); break;
    case Resource::Type::Material: ret = shared_ptr<Resource>(new ResourceMaterial(uid)); break;
    case Resource::Type::Shader: ret = shared_ptr<Resource>(new ResourceShader(uid)); break;
    case Resource::Type::UNKNOWN:return nullptr; break;
    default: break;
    }
    if (ret != nullptr)
    {
        ret->name = path.stem().string();
        if ( type == Resource::Type::Material)
        {
            std::filesystem::path tmp = path.string();
            tmp.replace_extension(".material");
            ret->SetAssetPath(tmp.string());

        }
        else {
            ret->SetAssetPath(path.string());
        }
        Debug::Log("Importing new asset:" + ret->GetAssetPath().stem().string());
        resources.insert(std::make_pair(ret->GetAssetPath().string(), std::make_pair(uid, ret)));
    }
    return ret;
}

shared_ptr<Resource> ResourcesManagement::CreateRawResource(Resource::Type type)
{
    shared_ptr<Resource> ret;

    switch (type) {
    case Resource::Type::Texture: ret = shared_ptr<Resource>(new ResourceTexture()); break;
    case Resource::Type::Mesh: ret = shared_ptr<Resource>(new ResourceMesh()); break;
    case Resource::Type::Fbx: ret = shared_ptr<Resource>(new ResourceScene()); break;
    case Resource::Type::Material: ret = shared_ptr<Resource>(new ResourceMaterial()); break;
    case Resource::Type::Shader: ret = shared_ptr<Resource>(new ResourceShader()); break;
    case Resource::Type::UNKNOWN:return nullptr; break;
    default: break;
    }
    return ret;
}

void ResourcesManagement::RemoveResource(UID uid)
{
    auto it = resources.begin();
    while (it != resources.end())
    {
        if (uid == it->second.first)
        {
            resources.erase(it);
            return;
        }
        it++;
    }
}

void ResourcesManagement::LoadMetaFiles()
{
    filesystem::path entry = ASSETS_DIR;
    cout << "Loading meta files... \n";
    vector<filesystem::path>metafiles = SearchForFileType(entry, ".meta");
    //Load meta files
    for (const auto& file : metafiles)
    {
        //read meta file
        shared_ptr<Resource> resource(new Resource(file));

        auto tmp = GetResource(resource->GetID());
        if (tmp != nullptr)
            continue;

        //check that id file is stored in the project library
        // meaning we have the custom file 
        //if not load new resource 
        if (std::filesystem::exists(resource->GetLibraryPath()))
        {
            cout << "file exist in lib, loading resource...\n";
            Debug::Log("Loading asset: " + resource->GetID());

            switch (resource->GetType()) {
            case Resource::Type::Texture:
            {
                shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceTexture());
                *ret = *resource;
                ret->LoadData();
                resources.insert(std::make_pair(ret->GetAssetPath().string(), std::make_pair(ret->GetID(), ret)));
            }break;
            case Resource::Type::Mesh: {
                shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceMesh());
                *ret = *resource;
                ret->LoadData();
                resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            }break;
            case Resource::Type::Fbx: { 
                shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceScene());
                *ret = *resource;
                ret->LoadData();
                resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            }break;
            case Resource::Type::Material: {
                shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceMaterial());
                *ret = *resource;
                ret->LoadData();
                resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            }break;   
            case Resource::Type::Shader: {
                shared_ptr<Resource>  ret = shared_ptr<Resource>(new ResourceShader());
                *ret = *resource;
                ret->LoadData();
                resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
            }break;
            case Resource::Type::UNKNOWN: break;
            default: break;
            }
        }
        else {
           cout << "ERROR::RESOURCE_CUSTOM_FORMAT_NOT_FOUND\n";
           Debug::Log("Reimporting existing asset: " + resource->GetID());
           switch (resource->GetType())
           {
           case Resource::Type::Fbx: SceneImporter::Import(resource); break;
           case Resource::Type::Texture: TextureImporter::Import(resource); break;
           default:
               break;
           }
           resource->GenerateMetaFile(resource->GetAssetPath().string()+".meta");
           resources.insert(std::make_pair(resource->GetAssetPath().string(), std::make_pair(resource->GetID(), resource)));
        }
    }
}

std::string ResourcesManagement::MoveToAssets(const string disc_path)
{
    //once the file is something that we accept
    // move file from disk to the assets lib  
    std::size_t from = disc_path.find_last_of('/\\');
    std::string fileName = disc_path.substr(from + 1, ' ');
    std::string newPathFolder = "../Output/Assets/";
    std::string newPath = newPathFolder + fileName;

    //check if this asset is already in the program
    if (Exists(newPath))
    {
        cout << "file already exist: " << fileName <<  "\n";
        return newPath;
    }
    //store new file to assets
    if (rename(disc_path.c_str(), newPath.c_str()))
    {
        Debug::Warning("Couldn't load file: " + fileName);
        return "";
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
    std::size_t from = assets_path.find_last_of('\\');
    std::string fileName = assets_path.substr(from + 1, ' ');
    std::string newPathFolder = LIBRARY_DIR;
    return newPathFolder;
}

Resource::Type ResourcesManagement::FilterFile(const char* file_path)
{
    std::filesystem::path filePath = file_path;
    Resource::Type type = Resource::Type::UNKNOWN;
    if (filePath.extension() == ".fbx") // Heed the dot.
    {
        std::cout << filePath.filename() << " is a valid type.\n";
        type = Resource::Type::Fbx;
    }
    else if (filePath.extension() == ".dds")
    {
        std::cout << filePath.filename() << " is a valid type.\n";
        type = Resource::Type::Texture;
    }
    else if (filePath.extension() == ".png")
    {
        std::cout << filePath.filename() << " is a valid type.\n";
        type = Resource::Type::Texture;
    }
    else if (filePath.extension() == ".jpg")
    {
        std::cout << filePath.filename() << " is a valid type.\n";
        type = Resource::Type::Texture;
    } 
    else if (filePath.extension() == ".tga")
    {
        std::cout << filePath.filename() << " is a valid type.\n";
        type = Resource::Type::Texture;
    }
    else if (filePath.extension() == ".vertex")
    {
        std::cout << filePath.filename() << " is a valid type.\n";
        type = Resource::Type::Shader;
    }
    else if (filePath.extension() == ".meta")
    {
        type = Resource::Type::UNKNOWN;
    }
    else {
        std::cout << "unknown file type "<< filePath.filename() <<"\n";
        type = Resource::Type::UNKNOWN;
    }
    return type;
}

