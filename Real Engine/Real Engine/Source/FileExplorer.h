#pragma once
#include "Panel.h"
#include "Texture.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class FileExplorer :  public Panel
{
public :
	FileExplorer(int _id, bool isActive);
	~FileExplorer();
	void Init();
	void Update();
	bool CleanUp();
private:
	int directoryIcon;
	int fileIcon;
	fs::path currentDirectory;
};
static const char* FILE_SCENE_DROP = "FILE_SCENE_DROP";
