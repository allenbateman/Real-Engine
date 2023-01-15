#include "ResourceMaterial.h"
#include "Application.h"
#include "ResourcesManagement.h"
ResourceMaterial::ResourceMaterial(UID id) : Resource(id)
{
	type = Resource::Type::Material;
}

ResourceMaterial::ResourceMaterial()
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
			texture_json["uid"] = texture.second->GetID();
			texture_json["asset_path"] = texture.second->GetAssetPath();
			texture_json["lib_path"] = texture.second->GetLibraryPath();
			texture_json["type"] = texture.second->type;
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

			UID uid = texture["uid"].get<std::string>();
			std::string asset_path  = texture["asset_path"].get<std::string>();
			std::string lib_path  = texture["lib_path"].get<std::string>();
			std::string type  = texture["type"].get<std::string>();
			
			
			shared_ptr<Resource> resource = app->resourceManager->GetResource(uid);
			if (resource == nullptr)
			{
				resource = app->resourceManager->CreateRawResource(Resource::Type::Texture);
				resource->SetUID(uid);
				resource->SetAssetPath(asset_path);
				resource->SetLibraryPath(lib_path);
				resource->name = GetAssetPath().stem().string();
				app->resourceManager->AddResource(resource);
			}			
			shared_ptr<ResourceTexture>  rtexture = dynamic_pointer_cast<ResourceTexture>(resource);
			rtexture->type = type;
			pair<std::string, shared_ptr<ResourceTexture>> tex(asset_path, rtexture);
			textures.push_back(tex);
		}

		//load shader
		UID uid = material["shader"]["uid"].get<std::string>();
		std::string vertPath = material["shader"]["vertex_path"];
		std::string fragPath = material["shader"]["fragment_path"];

		shared_ptr<Resource> resource = app->resourceManager->GetResource(uid);

		if (resource == nullptr)
		{
			resource = app->resourceManager->CreateRawResource(Resource::Type::Shader);
			resource->SetUID(uid);
			resource->SetAssetPath(vertPath);
			resource->name = name;
			app->resourceManager->AddResource(resource);
		}

		shared_ptr<ResourceShader> rShader = dynamic_pointer_cast<ResourceShader>(resource);
		rShader->vertex = vertPath;
		rShader->fragment = fragPath;
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
