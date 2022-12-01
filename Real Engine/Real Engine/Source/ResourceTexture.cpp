#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(UID uid) : Resource(uid)
{
	type = Type::Texture;
}

ResourceTexture::~ResourceTexture()
{
}

//Material operators--------------------------------
std::ostream& operator <<(std::ostream& out, const ResourceTexture& resource)
{
    out << "<id>" << resource.GetID().c_str();
    out << "<assets>" << resource.GetAssetPath();
    out << "<library>" << resource.GetLibraryPath();
    out << "\n";
    out << "<width>" << resource.width;
    out << "<height>" << resource.height;
    out << "<type>" << resource.type;
    out << "<format>" << resource.format;
    out << "<depth>" << resource.depth;
    out << "<channels>" << resource.channels;

    return out;
}
void ResourceTexture::Save() const
{
    std::ofstream out(assetsPath+".meta");
    if (out.is_open())
    {
        out << *this << '\n';
    }
    else {
        std::cout << "Error creating meta file" + uid;
    }
}

void ResourceTexture::Load() const
{
}

void ResourceTexture::UnLoad() const
{
}