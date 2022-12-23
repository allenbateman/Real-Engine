#include "ResourceTexture.h"
#include "Importer.h"
#define STB_IMAGE_IMPLEMENTATION
#include <Stb/stb_image.h>
ResourceTexture::ResourceTexture(UID uid) : Resource(uid)
{
	SetType(Type::Texture);
}

ResourceTexture::~ResourceTexture()
{
}

std::ostream& operator <<(std::ostream& out, const ResourceTexture& resource)
{
    out << "name:" << resource.name << '\n';
    out << "id:" << resource.GetID().c_str() << "\n";
    out << "assets path:" << resource.GetAssetPath().c_str() << "\n";
    out << "library path:" << resource.GetLibraryPath().c_str() << "\n";
    out << "resource type:" << (int) resource.GetType() << "\n";
    out << "width:" << resource.width << "\n";
    out << "height:" << resource.height << "\n";
    out << "type:" << resource.type << "\n";
    out << "format:" << resource.format << "\n";
    out << "depth:" << resource.depth << "\n";
    out << "channels:" << resource.channels << "\n";

    return out;
}
std::ifstream& operator >>(std::ifstream& in, ResourceTexture& Resource)
{
    

    return in;
}
void ResourceTexture::Save() const
{
    std::ofstream out(assetsPath.string() + ".meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
    out.close();
}

void ResourceTexture::Load() const
{
    //TODO check file path if its already flipped, the don,t flip 
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
    unsigned char* data = stbi_load(librayPath.string().c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        LOG("Succesfully loaded texture:%i ", texture);
        LOG(librayPath.string().c_str());
    }
    else
    {
        LOG("Failed to load texture: ");
        LOG(librayPath.string().c_str());
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    texture;
}

void ResourceTexture::UnLoad() const
{
   // glDeleteTextures(1,&renderId);

}

void ResourceTexture::Load(std::shared_ptr<Resource>& resource,std::ifstream& data)
{
    auto rt = std::static_pointer_cast<ResourceTexture>(resource);

    if (data.is_open())
    {       
        std::string val;
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->width = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->height = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->type = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->format = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->depth = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        rt->channels = stoi(val);       

        app->importer->importedTextures.push_back(rt->GetAssetPath().c_str());
    }
    data.close();
}

void ResourceTexture::Load(std::ifstream& data)
{
    if (data.is_open())
    {
        std::string val;
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        width = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        height = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        type = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        format = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        depth = stoi(val);
        std::getline(data, val, ':');
        std::getline(data, val, '\n');
        channels = stoi(val);

        app->importer->importedTextures.push_back(GetAssetPath().c_str());
    }
    data.close();
}
