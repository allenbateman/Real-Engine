#pragma once
#include "Resource.h"
#include "Material.h"
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
    void Load(std::ifstream& data) override;
    std::vector<std::pair<std::string, std::shared_ptr<ResourceTexture>>> resourcesTexture;
    Material material;
};

