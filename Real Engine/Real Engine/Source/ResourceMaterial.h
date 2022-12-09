#pragma once
#include "Resource.h"
#include "ResourceTexture.h"
class ResourceMaterial : public Resource
{
public:
	ResourceMaterial(UID id);
	~ResourceMaterial();

    void Save()const;
    void Load() const;
    void UnLoad()const;
    static std::shared_ptr<Resource> Load(std::shared_ptr<Resource> resource, std::ifstream& data);
    std::vector<std::pair<std::string, ResourceTexture>> resourcesTexture;
};

