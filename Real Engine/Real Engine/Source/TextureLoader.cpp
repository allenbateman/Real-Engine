#include "TextureLoader.h"
#include "Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "External/Stb/stb_image.h"
unsigned int LoadTexture(std::string file_path)
{
    //TODO check file path if its already loaded, the don,t flip 
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    int width, height, nrChannels;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        LOG("Succesfully loaded texture:%i ",texture);
        LOG(file_path.c_str());
    }
    else
    {
        LOG("Failed to load texture: ");
        LOG(file_path.c_str());
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
};