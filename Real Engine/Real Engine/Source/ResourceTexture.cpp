#include "ResourceTexture.h"
#include "Importer.h"
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
    out << "assets path:" << resource.GetAssetPath() << "\n";
    out << "library path:" << resource.GetLibraryPath() << "\n";
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
    std::ofstream out(assetsPath+".meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
    out.close();
}

void ResourceTexture::Load() const
{
   
}

void ResourceTexture::UnLoad() const
{
}

Resource* ResourceTexture::Load(Resource* resource,std::ifstream& data)
{
    ResourceTexture* rt = static_cast<ResourceTexture*>(resource);
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

        app->importer->importedTextures.push_back(rt->GetAssetPath());
    }

    data.close();
    return rt;
}
