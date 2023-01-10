#pragma once
#include "Resource.h"
#include "Texture.h"
class ResourceTexture : public Resource
{
public: 
    ResourceTexture(UID uid);
    ~ResourceTexture();

    void Save()const;
    void Load();
    void UnLoad()const;
    static void Load(std::shared_ptr<Resource>& resource,std::ifstream& data );
    void Load(std::ifstream& data) override;
public:
    Texture texture;
    int width;
    int height;
    int channels;
    int format;
    int depth;
    int type;
    int flipped;
};

