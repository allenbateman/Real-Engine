#include "ResourceScene.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
ResourceScene::ResourceScene(UID uid): Resource(uid)
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

        for (auto child : root->GetComponent<Transform>().childs)
        {
            nlohmann::json child_json;
            child_json["name"] = child->owner->name;
            child_json["transform"]["position"] = 
            {
                {"x",child->position.x},
                {"y",child->position.y},
                {"z",child->position.z}
            };
            child_json["transform"]["scale"] = {
                {"x",child->scale.x},
                {"y",child->scale.y},
                {"z",child->scale.z}
            };
            child_json["transform"]["rotation"] = {
                {"x",child->rotation.x},
                {"y",child->rotation.y},
                {"z",child->rotation.z},
                {"w",child->rotation.w}
            };          

            if (child->owner->HasComponent<Mesh>())
            {
                auto mesh = child->owner->GetComponent<Mesh>();
                child_json["mesh"]["uid"] = mesh.resource->GetID();
                child_json["mesh"]["path"] = mesh.resource->GetAssetPath();
                child_json["mesh"]["material_index"] = mesh.resource->material_UID;
            }
            if (child->owner->HasComponent<Material>())
            {
                auto material = child->owner->GetComponent<Material>();
                child_json["material"]["uid"] = material.resource->GetID();
                child_json["material"]["path"] = material.resource->GetAssetPath();
                child_json["material"]["shader"]["uid"] = material.resource->shader->GetID();
                child_json["material"]["shader"]["path"] = material.resource->shader->GetAssetPath();
            }
        }     
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
    }
    in.close();
}

void ResourceScene::Load()
{
}

void ResourceScene::UnLoad()
{
}
