#include "ResourceTexture.h"
#include "Importer.h"
#include "UiSystem.h"
#include <DevIL/ilu.h>
#include "TextureLoader.h"

ResourceTexture::ResourceTexture(UID uid) : Resource(uid)
{
	SetType(Type::Texture);
}

ResourceTexture::~ResourceTexture()
{
}

std::ostream& operator <<(std::ostream& out, const ResourceTexture& resource)
{
    out << "name:" << resource.name << '\n';
    out << "id:" << resource.GetID().c_str() << "\n";
    out << "assets path:" << resource.GetAssetPath().string().c_str() << "\n";
    out << "library path:" << resource.GetLibraryPath().string().c_str() << "\n";
    out << "resource type:" << (int) resource.GetType() << "\n";
    out << "width:" << resource.width << "\n";
    out << "height:" << resource.height << "\n";
    out << "type:" << resource.type << "\n";
    out << "format:" << resource.format << "\n";
    out << "depth:" << resource.depth << "\n";
    out << "channels:" << resource.channels << "\n";

    return out;
}
std::ifstream& operator >>(std::ifstream& in, ResourceTexture& Resource)
{
    

    return in;
}
void ResourceTexture::Save() const
{
    std::ofstream out(assetsPath.string() + ".texture.meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
    out.close();


    //std::ofstream out(filename);
    //if (out.is_open())
    //{
    //    nlohmann::json json_obj;
    //    json_obj["uid"] = tex.uid;
    //    json_obj["id"] = tex.id;
    //    json_obj["path"] = tex.path;
    //    json_obj["type"] = tex.type;
    //    std::string json_str = json_obj.dump();
    //    out << json_str.c_str();
    //}
    //out.close();
}

void ResourceTexture::Load()
{
    if (IsLoaded) return;

    unsigned int id = LoadTexture(librayPath.string());

    if (id == 0)
    {
        IsLoaded = false;
        texture.id = id;
        Debug::Log("Error loading texture..." + name);
        return;
    }
    IsLoaded = true;
    texture.id = id;
}

void ResourceTexture::UnLoad() const
{
    glDeleteTextures(1,&texture.id);
}

void ResourceTexture::Load(std::shared_ptr<Resource>& resource,std::ifstream& data)
{
    auto rt = std::static_pointer_cast<ResourceTexture>(resource);

    if (data.is_open())
    {       
        std::string val;
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->width = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->height = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->type = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->format = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->depth = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->channels = stoi(val);       

        app->importer->importedTextures.push_back(rt->GetAssetPath().c_str());
    }
    data.close();
}

void ResourceTexture::LoadMetaData(std::ifstream& data)
{
    if (data.is_open())
    {
        std::string val;
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        width = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        height = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        type = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        format = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        depth = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        channels = stoi(val);

        app->importer->importedTextures.push_back(GetAssetPath().c_str());
    }
    data.close();
}

void ResourceTexture::GenerateMetaFile()
{
}
