#include "ResourceScene.h"
#include "ResourcesManagement.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Tag.h"

ResourceScene::ResourceScene(UID uid): Resource(uid)
{
	type = Type::Fbx;
}

ResourceScene::ResourceScene()
{
    type = Type::Fbx;
}

ResourceScene::~ResourceScene()
{
}

void ResourceScene::SaveData()
{
    std::ofstream out;
    out.open(libraryPath);
    if (out.is_open())
    {
        nlohmann::json scene;
        scene["name"] = name;
        scene["uid"] = uid;
        scene["mehses"] = nlohmann::json::array();
        for (auto mesh : meshes)
        {
            nlohmann::json mesh_json;
            mesh_json["uid"] = mesh.c_str();
            scene["mehses"].push_back(mesh_json);
        }
        scene["materials"] = nlohmann::json::array();
        for (auto material : materials)
        {
            nlohmann::json material_json;
            material_json["uid"] = material.c_str();
            scene["materials"].push_back(material_json);
        }
        scene["root"] = nlohmann::json::array();
        scene["root"].push_back(SaveNodeData(root->GetComponent<Transform>()));
        
        
        std::string json_str = scene.dump();
        out << json_str.c_str();
    }
    out.close();
}

void ResourceScene::LoadData()
{
    std::ifstream in;
    in.open(libraryPath);
    if (in.is_open())
    {
        nlohmann::json scene;
        in >> scene;
        name = scene["name"].get<std::string>();
        for (const auto mesh : scene["meshes"])
        {
            meshes.push_back(mesh["uid"]);
        }
        for (const auto material : scene["materials"])
        {
            materials.push_back(material["uid"]);
        }
        root = new GameObject(name);
        if (scene.contains("root"))
        {
            LoadNodeData(scene["root"].front(), root);
        }
    }
    in.close();
    Load();
 
}

void ResourceScene::Load()
{

    for (auto mesh : meshes)
    {
        auto resource = app->resourceManager->GetResource(mesh);
        if (resource != nullptr)
        {
                resource->Load();
        }
    }
    for (auto material : materials)
    {
        auto resource = app->resourceManager->GetResource(material);
        if (resource != nullptr) 
        {
            resource->Load();
        }
    }
    app->sceneManager->currentScene->AddGameObject(root);
}

void ResourceScene::UnLoad()
{
}

void ResourceScene::LoadNodeData(nlohmann::json& node,GameObject* root)
{
  
    root->name = node["name"].get<string>();
    std::cout << "Laoding: " << root->name <<"\n";
    root->GetComponent<TagComponent>() = node["name"].get<string>();;
    if (root->name == "City_building_007")
    {
        std::cout << "stop\n";
    }

    auto& transform = root->GetComponent<Transform>();
    transform.localPosition.x = node["transform"]["position"]["x"].get<float>();
    transform.localPosition.y = node["transform"]["position"]["y"].get<float>();
    transform.localPosition.z = node["transform"]["position"]["z"].get<float>();
    
    transform.eulerAngles.x = node["transform"]["rotation"]["x"].get<float>();
    transform.eulerAngles.y = node["transform"]["rotation"]["y"].get<float>();
    transform.eulerAngles.z = node["transform"]["rotation"]["z"].get<float>();

    transform.localScale.x = node["transform"]["scale"]["x"].get<float>();
    transform.localScale.y = node["transform"]["scale"]["y"].get<float>();
    transform.localScale.z = node["transform"]["scale"]["z"].get<float>();

    transform.localMatrix.translate(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);
    transform.localMatrix.rotate(transform.eulerAngles.x, transform.eulerAngles.y, transform.eulerAngles.z);

    if (node.contains("mesh"))
    {
        auto uid = node["mesh"]["uid"].get<UID>();
        auto assetPath = node["mesh"]["asset_path"].get<std::string>();
        auto libpath = node["mesh"]["lib_path"].get<std::string>();
        auto name = node["mesh"]["name"].get<std::string>();

        shared_ptr<Resource> resource = app->resourceManager->GetResource(uid);
        Mesh mesh;
        if (resource == nullptr)
        {
            resource = app->resourceManager->CreateRawResource(Resource::Type::Mesh);
            resource->SetUID(uid);
            resource->SetAssetPath(assetPath);
            resource->SetLibraryPath(libpath);
            resource->name = name;
            meshes.push_back(uid);
            app->resourceManager->AddResource(resource);
            mesh.resource = static_pointer_cast<ResourceMesh>(resource);
            mesh.resource->LoadData();
        }
        else {
            mesh.resource = static_pointer_cast<ResourceMesh>(resource);
        }

        root->AddComponent<Mesh>(mesh);
    }
    if (node.contains("material"))
    {
        auto uid = node["material"]["uid"].get<UID>();
        auto assetPath = node["material"]["asset_path"].get<std::string>();
        auto libpath = node["material"]["lib_path"].get<std::string>();
        auto name = node["material"]["name"].get<std::string>();
        //check if resource exist
        auto resource = app->resourceManager->GetResource(uid);
        Material material;
        if (resource == nullptr)
        {
            //if not load resource
            resource = app->resourceManager->CreateRawResource(Resource::Type::Material);
            resource->SetUID(uid);
            resource->SetAssetPath(assetPath);
            resource->SetLibraryPath(libpath);
            resource->name = name;
            materials.push_back(uid);
            app->resourceManager->AddResource(resource);
            material.resource = static_pointer_cast<ResourceMaterial>(resource);
            material.resource->LoadData();
        }
        else
        {
            material.resource = static_pointer_cast<ResourceMaterial>(resource);
        }
        //add material as component
        root->AddComponent<Material>(material);
    }
    for (auto child : node["node"])
    {
        GameObject newObj = *(new GameObject());;
        LoadNodeData(child, &newObj);
        newObj.GetComponent<Transform>().parent = &root->GetComponent<Transform>();
        root->GetComponent<Transform>().AddChild(&newObj.GetComponent<Transform>());
        root->childsCount++;
    }

}

nlohmann::json ResourceScene::SaveNodeData(Transform& root)
{
     nlohmann::json child_json;
     child_json["name"] = root.owner->name;
     child_json["transform"]["position"] =
     {
         {"x",root.localPosition.x},
         {"y",root.localPosition.y},
         {"z",root.localPosition.z}
     };
     child_json["transform"]["scale"] = {
         {"x",root.localScale.x},
         {"y",root.localScale.y},
         {"z",root.localScale.z}
     };
     child_json["transform"]["rotation"] = {
         {"x",root.eulerAngles.x},
         {"y",root.eulerAngles.y},
         {"z",root.eulerAngles.z}
     };

     if (root.owner->HasComponent<Mesh>())
     {
         auto mesh = root.owner->GetComponent<Mesh>();

         child_json["mesh"]["uid"] = mesh.resource->GetID();
         child_json["mesh"]["asset_path"] = mesh.resource->GetAssetPath();
         child_json["mesh"]["lib_path"] = mesh.resource->GetLibraryPath();
         child_json["mesh"]["name"] = mesh.resource->name;
     }
     if (root.owner->HasComponent<Material>())
     {
         auto material = root.owner->GetComponent<Material>();
         child_json["material"]["uid"] = material.resource->GetID();
         child_json["material"]["asset_path"] = material.resource->GetAssetPath();
         child_json["material"]["lib_path"] = material.resource->GetLibraryPath();
         child_json["material"]["name"] = material.resource->name;
         child_json["material"]["shader"]["uid"] = material.resource->shader->GetID();
         child_json["material"]["shader"]["path"] = material.resource->shader->GetAssetPath();
     }
     if (!root.childs.empty())
     {
         child_json["node"] = nlohmann::json::array();
         for (const auto& child : root.childs)
             child_json["node"].push_back(SaveNodeData(*child));
     }
     return child_json;
}
