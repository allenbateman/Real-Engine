#pragma once
#include "Panel.h"
#include "Texture.h"
#include <iostream>
//#include <boost/filesystem.hpp>


class FileExplorer :  public Panel
{
public :
	FileExplorer(int _id, bool isActive);
	~FileExplorer();
	void Init();
	void Update();
	bool CleanUp();
private:
	Texture directoryIcon;
	Texture fileIcon;

};

