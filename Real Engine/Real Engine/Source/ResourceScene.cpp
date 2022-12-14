#include "ResourceScene.h"

ResourceScene::ResourceScene(UID uid): Resource(uid)
{
	type = Type::Fbx;
}

ResourceScene::~ResourceScene()
{
}
std::ostream& operator <<(std::ostream& out, const ResourceScene& resource)
{
    out << "name:" << resource.name<<'\n';
    out << "id:" << resource.GetID().c_str() << "\n";
    out << "assets path:" << resource.GetAssetPath().string() << "\n";
    out << "library path:" << resource.GetLibraryPath().string() << "\n";
    out << "resource type:" << (int)resource.GetType() << "\n";
    out << "materials count:" << resource.materials.size() << "\n";
    for (int i = 0; i < resource.materials.size(); i++)
    {
        out << "\t uid " << i << ":" << resource.materials.at(i) << "\n";
    }
    out << "mesh count :" << resource.meshes.size() << "\n";
    for (int i = 0; i < resource.meshes.size(); i++)
    {
        out << "\t uid " << i << ":" << resource.meshes.at(i) <<"\n";
    }
    out << "\tname: " << resource.GetRoot().name << "\n";
    out << "\tchild count: " << resource.GetRoot().childsCount << "\n";
    for (const auto& node : resource.root->childs)
    {
        out << "\tname: " << node.name << "\n";
        out << "\tchild count: " << node.childsCount << "\n";
        out << "\tmesh count: " << node.meshCount << "\n";
        for (auto& i : node.meshIndex)
        {
            out << "\tmesh index: " << node.meshIndex[i] << "\n";
        }
    }
    return out;
}
void ResourceScene::Save() const
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

void ResourceScene::Load() const
{
}

void ResourceScene::UnLoad() const
{
}

void ResourceScene::Load(std::shared_ptr<Resource>& resource, std::ifstream& data)
{
    std::shared_ptr<ResourceScene> obj = std::static_pointer_cast<ResourceScene>(resource);
    if (data.is_open())
    {
        //Load fbx
        std::string nNodes;
        std::getline(data, nNodes, ':');
        std::getline(data, nNodes, '\n');

        for (int i = 0; i < stoi(nNodes); i++)
        {

            SceneNode node;
            std::string name;
            std::getline(data, name, ':');
            std::getline(data, name, '\n');
            node.name = name;
            std::string nChilds;
            std::getline(data, nChilds, ':');
            std::getline(data, nChilds, '\n');
            node.childsCount = stoi(nChilds);
    /*        for (int n = 0; n < node.childsCount; n++)
            {
                std::string type;
                std::getline(data, type, ':');
                std::getline(data, type, '\n');

                Resource::Type t = static_cast<Resource::Type>(stoi(type));

                UID r;
                std::getline(data, r, ':');
                std::getline(data, r, '\n');

                std::pair<Resource::Type, UID> p{t,r};
                node.resources.push_back(p);
            }
            obj->nodes.push_back(node);*/
        }
    }

    data.close();
}
