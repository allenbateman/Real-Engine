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
    out << "assets path:" << resource.GetAssetPath().c_str() << "\n";
    out << "library path:" << resource.GetLibraryPath().c_str() << "\n";
    out << "resource type:" << (int)resource.GetType() << "\n";
    out << "materials count:" << resource.materials.size() << "\n";
    for (int i = 0; i < resource.materials.size(); i++)
    {
        out << "\t uid " << i << ":" << resource.materials.at(i);
    }
    out << "mesh count:" << resource.meshes.size() << "\n";
    for (int i = 0; i < resource.meshes.size(); i++)
    {
        out << "\t uid " << i << ":" << resource.meshes.at(i);
    }
    out << "\tname:" << resource.GetRoot().name << "\n";
    out << "\tchild count:" << resource.GetRoot().childsCount << "\n";
    for (const auto& node : resource.root->childs)
    {
        out << "\tname:" << node.name << "\n";
        out << "\tchild count:" << node.childsCount << "\n";

        //for (const auto& resource : node.meshCount)
        //{
        //    out << "\t\ttype:" << resource.first << "\n";
        //    out << "\t\tid:" << resource.second << "\n";           
        //}
    }
    return out;
}
void ResourceFbx::Save() const
{
    std::ofstream out(assetsPath.string() + ".meta");
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

void ResourceFbx::Load(std::shared_ptr<Resource>& resource, std::ifstream& data)
{
    std::shared_ptr<ResourceFbx> obj = std::static_pointer_cast<ResourceFbx>(resource);
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
            //for (int n = 0; n < node.childsCount; n++)
            //{
            //    std::string type;
            //    std::getline(data, type, ':');
            //    std::getline(data, type, '\n');

            //    Resource::Type t = static_cast<Resource::Type>(stoi(type));

            //    UID r;
            //    std::getline(data, r, ':');
            //    std::getline(data, r, '\n');

            //    std::pair<Resource::Type, UID> p{t,r};
            //    node.resources.push_back(p);
            //}
            //obj->nodes.push_back(node);
        }
    }

    data.close();
}
