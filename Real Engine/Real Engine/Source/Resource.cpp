#include "Resource.h"

Resource::Resource(UID id)
{
    uid = id;
}
Resource::Resource(std::filesystem::path path)
{
	std::ifstream inputFile(path);
	if (inputFile.is_open())
	{
		nlohmann::json data;
		inputFile >> data;

		name = data["name"].get<std::string>();
		uid = data["uid"].get<UID>();
		assetsPath = data["assets_path"].get<std::filesystem::path>();
		libraryPath = data["lib_path"].get<std::filesystem::path>();
		type = data["resource_type"].get<Resource::Type>();
	}

	inputFile.close();
}
void Resource::SetType(Resource::Type type)
{
   this->type = type;
}

Resource::Type Resource::GetType() const
{
    return type;
}

UID Resource::GetID() const
{
    return uid;
}


bool Resource::IsLoadedToMemory() const
{
    return false;
}

unsigned int Resource::GetRefereneCount() const
{
    return 0;
}

void Resource::SaveData()
{
}

void Resource::LoadData()
{
}

void Resource::Load()
{
}

void Resource::UnLoad()
{
}


void Resource::GenerateMetaFile(std::string path)
{
	std::ofstream out(path);
	if (out.is_open())
	{
		nlohmann::json json_obj;
		json_obj["name"] = name;
		json_obj["uid"] = uid;
		json_obj["assets_path"] = assetsPath.string();
		json_obj["lib_path"] = libraryPath.string();
		json_obj["resource_type"] = type;
		std::string json_str = json_obj.dump();
		out << json_str.c_str();
	}
	out.close();
}

void Resource::LoadMetaData(std::string path)
{
	std::ifstream data;
	data.open(path);
	if (data.is_open())
	{
		nlohmann::json data;
		name = data["name"].get<std::string>();
		uid = data["uid"].get<UID>();
		assetsPath = data["assets_path"].get<std::filesystem::path>();
		libraryPath = data["lib_path"].get<std::filesystem::path>();
		type = data["resource_type"].get<Resource::Type>();
	}

	data.close();
}

const char* Resource::GetTypeChar()
{
	switch (type)
	{
	case Resource::Type::UNKNOWN:
		return "unknown";
	case Resource::Type::Texture:
		return "Texture";
	case Resource::Type::Material:
		return "Material";
	case Resource::Type::Mesh:
		return "Mesh";
	case Resource::Type::Fbx:
		return "Fbx";
	case Resource::Type::GObject:
		return "Gameobject";
	case Resource::Type::Shader:
		return "Shader";
	case Resource::Type::Scene:
		return "Scene";
	default:
		break;
	}
}
