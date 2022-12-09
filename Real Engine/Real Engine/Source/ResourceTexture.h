#pragma once
#include "Resource.h"
class ResourceTexture : public Resource
{
public: 
    ResourceTexture(UID uid);
    ~ResourceTexture();

    void Save()const;
    void Load() const;
    void UnLoad()const;
    static void Load(std::shared_ptr<Resource>& resource,std::ifstream& data );
public:

    int width;
    int height;
    int channels;
    int format;
    int depth;
    int type;
    int flipped;
};

