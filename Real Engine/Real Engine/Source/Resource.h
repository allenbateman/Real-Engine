#pragma once
#include<iostream>
#include <string>
#include <fstream>  
#include <filesystem>  

using UID = std::string;

class Resource
{
public:
	enum class Type {
		UNKNOWN,
		Texture,
		Mesh,
		Shader,
		Scene,
		GObject,
		Fbx,
		Material
	};

	Resource(UID id);
	virtual ~Resource() {};

	void SetType(Resource::Type type);
	Resource::Type GetType() const;
	UID GetID()const;

	const std::filesystem::path GetAssetPath() const { return assetsPath; };
	const std::filesystem::path GetLibraryPath() const { return librayPath; };

	bool IsLoadedToMemory() const;
	bool LoadToMemory();
	unsigned int GetRefereneCount() const;

	virtual void Save()const;
	virtual void Load()const;
	virtual void UnLoad()const;

	void SetAssetPath(std::string  assets_path) { assetsPath = assets_path; };
	void SetLibraryPath(std::string  library_path) { librayPath = library_path; };

	std::string name;
	bool IsLoaded;

	const char* GetTypeChar();

protected:
	std::filesystem::path  assetsPath;
	std::filesystem::path librayPath;

	UID uid;
	Type type = Type::UNKNOWN;

public:
	const char* operator = (Resource::Type& type)
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
};

//const char* operator << (Resource::Type& type)
//{
//	switch (type)
//	{
//	case Resource::Type::UNKNOWN:
//		return "unknown";
//	case Resource::Type::Texture:
//		return "Texture";
//	case Resource::Type::Material:
//		return "Material";
//	case Resource::Type::Mesh:
//		return "Mesh";
//	case Resource::Type::Fbx:
//		return "Fbx";
//	case Resource::Type::GObject:
//		return "Gameobject";
//	case Resource::Type::Shader:
//		return "Shader";
//	case Resource::Type::Scene:
//		return "Scene";
//	default:
//		break;
//	}
//}