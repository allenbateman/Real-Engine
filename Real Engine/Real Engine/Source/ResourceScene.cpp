#include "ResourceScene.h"
#include "Transform.h"
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

    Transform t = resource.root->GetComponent<Transform>();
    out << "scene objects count :" << t.childs.size() << "\n";

    for (int i = 0; i < t.childs.size(); i++)
    {


        //get all childs, and for each child get the mesh and material it uses and also save other type of components
       // out << "\t uid " << i << ":" << resource.root->FindChild(i) << "\n";
    }

    return out;
}
void ResourceScene::Save() const
{
    std::ofstream out(assetsPath.string() + ".scene.meta");
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
    std::shared_ptr<ResourceScene> scene = std::static_pointer_cast<ResourceScene>(resource);
    if (data.is_open())
    {
        //get how many resources types the scene uses
        std::string materials;
        std::getline(data, materials, ':');
        std::getline(data, materials, '\n');
        
        for (int ii = 0; ii < stoi(materials); ii++)
        {
           std::string id;
           std::getline(data, id, ':');
           std::getline(data, id, '\n');
           scene->materials.push_back(id);
        }

        //get how many resources types the scene uses
        std::string meshes;
        std::getline(data, meshes, ':');
        std::getline(data, meshes, '\n');

        for (int ii = 0; ii < stoi(meshes); ii++)
        {
            std::string id;
            std::getline(data, id, ':');
            std::getline(data, id, '\n');
            scene->meshes.push_back(id);
        }        
        
        //get how many obj the scene uses
        std::string objsCount;
        std::getline(data, objsCount, ':');
        std::getline(data, objsCount, '\n');

        //for (int ii = 0; ii < stoi(objsCount); ii++)
        //{
        //    std::string id;
        //    std::getline(data, id, ':');
        //    std::getline(data, id, '\n');
        //    scene->meshes.push_back(id);
        //}
    }

    data.close();
}

void ResourceScene::Load(std::ifstream& data)
{
    if (data.is_open())
    {
        //get how many resources types the scene uses
        std::string materialCount;
        std::getline(data, materialCount, ':');
        std::getline(data, materialCount, '\n');

        for (int ii = 0; ii < stoi(materialCount); ii++)
        {
            std::string id;
            std::getline(data, id, ':');
            std::getline(data, id, '\n');
            materials.push_back(id);
        }

        //get how many resources types the scene uses
        std::string mesheCount;
        std::getline(data, mesheCount, ':');
        std::getline(data, mesheCount, '\n');

        for (int ii = 0; ii < stoi(mesheCount); ii++)
        {
            std::string id;
            std::getline(data, id, ':');
            std::getline(data, id, '\n');
            meshes.push_back(id);
        }

        //get how many obj the scene uses
        std::string objsCount;
        std::getline(data, objsCount, ':');
        std::getline(data, objsCount, '\n');

        //for (int ii = 0; ii < stoi(objsCount); ii++)
        //{
        //    std::string id;
        //    std::getline(data, id, ':');
        //    std::getline(data, id, '\n');
        //    scene->meshes.push_back(id);
        //}
    }

    data.close();
}
