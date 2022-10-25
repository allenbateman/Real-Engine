#pragma once
#include"Component.h"
#include<string>
struct Texture : Component
{
	//all the data is actually stored in the ram with opengl, so here we just 
	//need to store the reference to that texture in the ram
	unsigned int id;
	std::string path;
	std::string type;
};
