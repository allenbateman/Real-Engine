#include "ResourceFbx.h"

ResourceFbx::ResourceFbx(UID uid): Resource(uid)
{
	type = Type::Fbx;
}

ResourceFbx::~ResourceFbx()
{
}
std::ostream& operator <<(std::ostream& out, const ResourceFbx& resource)
{
    out << "name:" << resource.name<<'\n';
    out << "id:" << resource.GetID().c_str() << "\n";
    out << "assets path:" << resource.GetAssetPath() << "\n";
    out << "library path:" << resource.GetLibraryPath() << "\n";
    out << "resource type:" << (int)resource.GetType() << "\n";

    out << "Total nodes:" << resource.nodes.size() << "\n";
    for (const auto& node : resource.nodes)
    {
        out << "\tname:" << node.name << "\n";
        out << "\tchild count:" << node.childsCount << "\n";
        out << "\tresources count:" << node.reources.size() << "\n";
        for (const auto& resource : node.reources)
        {
            out << "\t id:" << resource << "\n";
        }
    }
    return out;
}
void ResourceFbx::Save() const
{
    std::ofstream out(assetsPath + ".meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
    out.close();
}

void ResourceFbx::Load() const
{
}

void ResourceFbx::UnLoad() const
{
}

Resource* ResourceFbx::Load(Resource* resource, std::ifstream& data)
{
    ResourceFbx* rt = static_cast<ResourceFbx*>(resource);
    if (data.is_open())
    {
        //Load fbx
        std::string nNodes;
        std::getline(data, nNodes, ':');
        std::getline(data, nNodes, '\n');

        for (int i = 0; i < stoi(nNodes); i++)
        {

            FbxNode node;
            std::string name;
            std::getline(data, name, ':');
            std::getline(data, name, '\n');
            node.name = name;
            std::string nChilds;
            std::getline(data, nChilds, ':');
            std::getline(data, nChilds, '\n');
            node.childsCount = stoi(nChilds);
            for (int n = 0; n < node.childsCount; n++)
            {
                UID r;
                std::getline(data, r, ':');
                std::getline(data, r, '\n');
                node.reources.push_back(r);
            }
            rt->nodes.push_back(node);
        }
    }

    data.close();
    return rt;
}
