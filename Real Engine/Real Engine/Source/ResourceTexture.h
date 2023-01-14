#pragma once
#include "Resource.h"
#include "Texture.h"
class ResourceTexture : public Resource
{
public: 
    ResourceTexture(UID uid);
    ~ResourceTexture();

    void SaveData();
    void LoadData();
    void Load();
    void UnLoad();

public:

    int width = 0;
    int height = 0;
    int channels = 0;
    int format = 0;
    int depth = 0;
    unsigned int id;//opengl render id
    std::string type; //what type of texture is
};

