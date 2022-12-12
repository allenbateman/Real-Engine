#include "ResourceMaterial.h"
#include "Application.h"
#include "ResourcesManagement.h"
ResourceMaterial::ResourceMaterial(UID id) : Resource(id)
{
	type = Resource::Type::Material;
}

ResourceMaterial::~ResourceMaterial()
{
}
std::ostream& operator <<(std::ostream& out, const ResourceMaterial& resource)
{
    out << "name:" << resource.name << '\n';
    out << "id:" << resource.GetID().c_str() << "\n";
    out << "assets path:" << resource.GetAssetPath().c_str() << "\n";
    out << "library path:" << resource.GetLibraryPath().c_str() << "\n";
    out << "resource type:" << (int)resource.GetType() << "\n";

    out << "Textures used:" << resource.resourcesTexture.size() << "\n";
    for (const auto& tex : resource.resourcesTexture)
    {
        out << "type:" << tex.first << "\n";
        out << "Textue id:" << tex.second.GetID() << "\n";
    }
    return out;
}
void ResourceMaterial::Save() const
{
    std::ofstream out(assetsPath.string() + ".material.meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
    out.close();
}

void ResourceMaterial::Load() const
{
}

void ResourceMaterial::UnLoad() const
{
}

void ResourceMaterial::Load(std::shared_ptr<Resource>& resource, std::ifstream& data)
{
    std::shared_ptr<ResourceMaterial> rm = std::static_pointer_cast<ResourceMaterial>(resource);
    if (data.is_open())
    {
        //laod vertices
        std::string nTex;
        std::getline(data, nTex, ':');
        std::getline(data, nTex, '\n');
        for (int i = 0; i < stoi(nTex); i++)
        {
            std::string textureType;
            std::getline(data, textureType, ':');
            std::getline(data, textureType, '\n');
            std::string id;
            std::getline(data, id, ':');
            std::getline(data, id, '\n');
            shared_ptr<Resource> r = app->resourceManager->GetResource(id);
            if (r == nullptr) break;
            shared_ptr<ResourceTexture> rt = dynamic_pointer_cast<ResourceTexture>(r);
            std::pair<std::string, ResourceTexture > tResource{ textureType,*rt };
            rm->resourcesTexture.push_back(tResource);

        }

    }

    data.close();
}
