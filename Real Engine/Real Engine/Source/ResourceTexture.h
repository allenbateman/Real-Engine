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
    void LoadMetaData(std::ifstream& data) override;
    void GenerateMetaFile() override;
public:
    Texture texture;
    int width = 0;
    int height = 0;
    int channels = 0;
    int format = 0;
    int depth = 0;
    unsigned int id;//opengl render id
    std::string type; //what type of texture is
};

