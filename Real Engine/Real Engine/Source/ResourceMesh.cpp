#include "ResourceMesh.h"


ResourceMesh::ResourceMesh(UID id) : Resource(id)
{

}
ResourceMesh::~ResourceMesh()
{

}
std::ostream& operator <<(std::ostream& out, const ResourceMesh& resource)
{
    out << "name:" << resource.name << '\n';
    out << "id:" << resource.GetID().c_str() << "\n";
    out << "assets path:" << resource.GetAssetPath().c_str() << "\n";
    out << "library path:" << resource.GetLibraryPath().c_str() << "\n";
    out << "resource type:" << (int)resource.GetType() << "\n";

    out << "material index:" << resource.materialIndex << "\n";
    return out;
}
void ResourceMesh::Save() const
{
    std::ofstream out(assetsPath.string() + ".mesh.meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
    out.close();
}

void ResourceMesh::Load() const
{
}

void ResourceMesh::UnLoad() const
{
}

std::shared_ptr<Resource>ResourceMesh::Load(std::shared_ptr<Resource> resource, std::ifstream& data)
{
    std::shared_ptr<ResourceMesh> rm = std::dynamic_pointer_cast<ResourceMesh>(resource);


    if (data.is_open())
    {
        //laod vertices
        std::string indices;
        std::getline(data, indices, ':');
        std::getline(data, indices, '\n');

        rm->materialIndex = stoi(indices);
    }

    data.close();
    return rm;
}
