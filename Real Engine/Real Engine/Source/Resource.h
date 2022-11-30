#pragma once
#include<iostream>

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
		GameObject,
		Fbx
	};
	Resource(UID id);
	~Resource();
	Resource::Type GetType();
	UID GetID()const;
	const char* GetAssetFile() const;
	const char* GetLibraryFile() const;

	bool IsLoadedToMemory() const;
	bool LoadToMemory();
	unsigned int GetRefereneCount() const;
	void IncreaseReferenceCount() { referenceCount++; };
	void DecreaseReferenceCount() { referenceCount--; if (referenceCount <= 0) UnLoad(); };

	virtual void Save()const;
	virtual void Load()const;
	virtual void UnLoad()const;

	void SetAssetPath(std::string  assets_path) { assetsPath = assets_path; };
	void SetLibraryPath(std::string  library_path) { librayPath = library_path; };
protected:
	std::string  assetsPath;
	std::string	 librayPath;
	UID uid;
	Type type = Type::UNKNOWN;

	unsigned int referenceCount = 0;
};

