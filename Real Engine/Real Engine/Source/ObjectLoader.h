#pragma once
#include <iostream>
#include "Log.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	bool LoadObject(const char* file_path);
	Mesh meshTest;
};

