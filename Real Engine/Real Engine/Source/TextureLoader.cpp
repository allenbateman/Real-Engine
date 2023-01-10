#include "TextureLoader.h"
#include <vector>
#include "Log.h"
#include "UiSystem.h"
#include <DevIL/ilu.h>

unsigned int LoadTexture(std::string file_path)//data
{
    // Load the image
    ILuint imageId;
    ilGenImages(1, &imageId);
    ilBindImage(imageId);
    if (!ilLoadImage(file_path.c_str()))
    {
        Debug::Log("Error loading texture...");
        return 0;
    }

    // check if the image needs to be flipped
    if (ilGetInteger(IL_IMAGE_ORIGIN) == IL_ORIGIN_UPPER_LEFT) {
        iluFlipImage();
    }
    // Convert the image to RGBA format
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    // Create the OpenGL texture
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

    // Clean up
    ilDeleteImages(1, &imageId);


    return textureId;
};