#include "ResourceTexture.h"
#include "Importer.h"
#include "UiSystem.h"
#include <DevIL/ilu.h>
#include "TextureLoader.h"


ResourceTexture::ResourceTexture(UID uid) : Resource(uid)
{
	SetType(Type::Texture);
}

ResourceTexture::~ResourceTexture()
{
}

void ResourceTexture::SaveData()
{
    string path = LIBRARY_DIR;
    std::string storePath = path + "Textures\\" + uid + ".dds";

    if (ilSave(IL_DDS, storePath.c_str()))
    {
        cout << "saved file with devil\n";
        SetLibraryPath(storePath);
    }
    else
    {
        cout << "could not save file with devil \n";
        return;
    }

}

void ResourceTexture::LoadData()
{
    if (ilLoadImage(GetLibraryPath().string().c_str()))
    {
        cout << "Texture  " << name << " loaded with devIL" << endl;
    }
    else {
        cout << "Texture not loaded with devIL " << name << endl;
        return;
    }

    ILubyte* data = ilGetData();
    ILenum type = ilGetInteger(IL_IMAGE_TYPE);
    width = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);
    depth = ilGetInteger(IL_IMAGE_DEPTH);
    channels = ilGetInteger(IL_IMAGE_CHANNELS);
    format = ilGetInteger(IL_IMAGE_FORMAT);
}

void ResourceTexture::Load()
{
    if (IsLoaded) return;

    unsigned int id = LoadTexture(libraryPath.string());

    if (id == 0)
    {
        IsLoaded = false;
        this->id = id;
        Debug::Log("Error loading texture..." + name);
        return;
    }
    IsLoaded = true;
    this->id = id;
}

void ResourceTexture::UnLoad() 
{
    glDeleteTextures(1,&id);
}
