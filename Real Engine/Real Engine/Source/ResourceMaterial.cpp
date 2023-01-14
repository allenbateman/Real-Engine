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
void ResourceMaterial::SaveData()
{
	std::ofstream out;
	out.open(libraryPath);
	if (out.is_open())
	{
		nlohmann::json material;
		material["textures"] = nlohmann::json::array();
		for (auto& texture : textures)
		{
			nlohmann::json texture_json;
			texture_json["path"] = texture.first;
			texture_json["uid"] = texture.second->GetID();
			material["textures"].push_back(texture_json);
		}
		nlohmann::json shader_json;
		shader_json["uid"] = shader->GetID();
		shader_json["vertex_path"] = shader->vertex.string();
		shader_json["fragment_path"] = shader->fragment.string();

		material["shader"] = shader_json;
		std::string json_str = material.dump();
		out << json_str.c_str();
	}
	out.close();
}
void ResourceMaterial::LoadData()
{
	std::ifstream in;
	in.open(libraryPath);
	if (in.is_open())
	{
		nlohmann::json material;
		in >> material;
		for (const auto& texture : material["textures"]) {

			std:string path  = texture["path"].get<std::string>();
			UID uid = texture["uid"].get<std::string>();
			shared_ptr<Resource> resource = app->resourceManager->GetResource(uid);
			if (resource == nullptr)
			{
				resource = app->resourceManager->CreateNewResource(path, Resource::Type::Texture);
			}
			shared_ptr<ResourceTexture>  rtexture = dynamic_pointer_cast<ResourceTexture>(resource);
			pair<std::string, shared_ptr<ResourceTexture>> tex(path, rtexture);
			textures.push_back(tex);
		}
		UID uid = material["shader"]["uid"].get<std::string>();
		std::string vertPath = material["shader"]["vertex_path"];
		std::string fragPath = material["shader"]["fragment_path"];

		shared_ptr<Resource> resource = app->resourceManager->GetResource(uid);

		if (resource == nullptr)
			resource = app->resourceManager->CreateNewResource(vertPath, Resource::Type::Shader);

		shared_ptr<ResourceShader> rShader = dynamic_pointer_cast<ResourceShader>(resource);
		rShader->Load(vertPath.c_str(), fragPath.c_str());

		shader = rShader;
	}
}

void ResourceMaterial::Load()
{
	for (auto& texture : textures)
	{
		texture.second->Load();
	}
	shader->Load();
}

void ResourceMaterial::UnLoad()
{
}
