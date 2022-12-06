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
    out << "assets path:" << resource.GetAssetPath() << "\n";
    out << "library path:" << resource.GetLibraryPath() << "\n";
    out << "resource type:" << (int)resource.GetType() << "\n";

    out << "indices:" << resource.indices << "\n";
    return out;
}
void ResourceMesh::Save() const
{
    std::ofstream out(assetsPath + ".mesh.meta");
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

Resource* ResourceMesh::Load(Resource* resource, std::ifstream& data)
{
    ResourceMesh* rm = static_cast<ResourceMesh*>(resource);


    if (data.is_open())
    {
        //laod vertices
        std::string indices;
        std::getline(data, indices, ':');
        std::getline(data, indices, '\n');

        rm->indices = stoi(indices);
    }

    data.close();
    return rm;
}
