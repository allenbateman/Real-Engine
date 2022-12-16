#pragma once
#include<iostream>
#include <string>
#include <fstream>  
#include <filesystem>  

using UID = std::string;

class Resource
{
public:
	enum Type {
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

protected:
	std::filesystem::path  assetsPath;
	std::filesystem::path librayPath;

	UID uid;
	Type type = Type::UNKNOWN;
};

