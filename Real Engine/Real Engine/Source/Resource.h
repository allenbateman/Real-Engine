#pragma once
#include<iostream>

using UID = unsigned int;

class Resource
{
public:
	enum Type {
		UNKNOWN,
		Texture,
		Mesh,
		Shader,
		Scene,
		GameObject,
		Fbx
	};
	Resource(UID id, Resource::Type type);
	~Resource();
	Resource::Type GetType(UID id);
	UID GetID()const;
	const char* GetAssetFile() const;
	const char* GetLibraryFile() const;

	bool IsLoadedToMemory() const;
	bool LoadToMemory();
	unsigned int GetRefereneCount() const;


	virtual void Save()const;
	virtual void Load()const;
	virtual void UnLoad()const;

protected:
	std::string  assetsFile;
	std::string	 librayFile;
	UID uid = 0;
	//Type type = UNKOWN;
	unsigned int referenceCount = 0;
};

