#pragma once
#include<iostream>
#include <string>
#include <fstream>  
#include <filesystem>  
#include "nlohmann/json.hpp"
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
	Resource();
	Resource(std::filesystem::path path);
	virtual ~Resource() {};

	void SetType(Resource::Type type);
	Resource::Type GetType() const;
	UID GetID()const;
	void SetUID(UID uid) { this->uid = uid; };

	const std::filesystem::path GetAssetPath() const { return assetsPath; };
	const std::filesystem::path GetLibraryPath() const { return libraryPath; };

	bool IsLoadedToMemory() const;
	unsigned int GetRefereneCount() const;


	virtual void SaveData();
	virtual void LoadData();
	virtual void Load();
	virtual void UnLoad();
	static Resource LoadFromMetaFile(std::string path);

	void GenerateMetaFile(std::string path);
	void LoadMetaData(std::string path);

	void SetAssetPath(std::string  assets_path) { assetsPath = assets_path; };
	void SetLibraryPath(std::string  library_path) { libraryPath = library_path; };

	std::string name;
	bool IsLoaded = false;
	bool IsDataLoaded = false;
	const char* GetTypeChar();

protected:
	std::filesystem::path assetsPath;
	std::filesystem::path libraryPath;

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