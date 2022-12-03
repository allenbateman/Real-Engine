#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(UID uid) : Resource(uid)
{
	SetType(Type::Texture);
}

ResourceTexture::~ResourceTexture()
{
}

//Material operators--------------------------------
std::ostream& operator <<(std::ostream& out, const ResourceTexture& resource)
{
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
}

void ResourceTexture::Load() const
{
   
}

void ResourceTexture::UnLoad() const
{
}

Resource* ResourceTexture::Load(std::string UUID,std::ifstream& data)
{
    Resource* ret = nullptr;
    if (data.is_open())
    {
        ResourceTexture* resource = new ResourceTexture(UUID);
        
        std::string val;
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        resource->width = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        resource->height = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        resource->type = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        resource->format = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        resource->depth = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        resource->channels = stoi(val);

        ret = (Resource*)resource;
    }

    data.close();


    return ret;
}
