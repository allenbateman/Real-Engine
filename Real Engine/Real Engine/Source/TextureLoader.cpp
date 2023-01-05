#include "TextureLoader.h"
#include <vector>
#include "Log.h"
#include <Stb/stb_image.h>
unsigned int LoadTexture(std::string file_path)//data
{
    //TODO check file path if its already flipped, the don,t flip 
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    int width, height, nrChannels,comp;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
   // unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    uint8_t* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels,0);
    //nrChannels = 4;
    std::vector<uint8_t> image_data;
    if (data)
    {
       //if the texture only has 3 channels convert it to 4
        if (nrChannels == 3)
        {
            image_data.resize(width * height * 4);
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int src_index = (y * width + x) * 3;
                    int dst_index = (y * width + x) * 4;
                    image_data[dst_index + 0] = data[src_index + 0];
                    image_data[dst_index + 1] = data[src_index + 1];
                    image_data[dst_index + 2] = data[src_index + 2];
                    image_data[dst_index + 3] = 255;
                }
            }
        }
        else if (nrChannels == 4)
        {
            image_data.resize(width * height * 4);
            std::memcpy(image_data.data(), data, image_data.size());
        }
       
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
        LOG("Succesfully loaded texture:%i ", texture);
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