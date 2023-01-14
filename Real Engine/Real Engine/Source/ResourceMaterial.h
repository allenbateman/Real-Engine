#pragma once
#include "Resource.h"
#include "ResourceShader.h"
#include "ResourceTexture.h"
class ResourceMaterial : public Resource
{
public:
	ResourceMaterial(UID id);
	~ResourceMaterial();

    void SaveData();
    void LoadData();
    void Load() ;
    void UnLoad();
    std::vector<std::pair<std::string, std::shared_ptr<ResourceTexture>>> textures;//string as path id and the resource itself
    std::shared_ptr<ResourceShader> shader;//shader to process the render 
};

