#pragma once
#include "Panel.h"
#include "Texture.h"
#include <iostream>
#include <filesystem>

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
