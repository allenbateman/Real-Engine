#pragma once
#include "Resource.h"
#include "ResourceShader.h"
#include "ResourceTexture.h"
class ResourceMaterial : public Resource
{
public:
	ResourceMaterial(UID id);
	~ResourceMaterial();

    void Save()const;
    void Load() const;
    void UnLoad()const;
    static void Load(std::shared_ptr<Resource>& resource, std::ifstream& data);
    void LoadMetaData(std::ifstream& data) override;
    void GenerateMetaFile() override;
    std::vector<std::pair<std::string, std::shared_ptr<ResourceTexture>>> textures;//string as path id and the resource itself
    std::shared_ptr<ResourceShader> shader;//shader to process the render 
};

