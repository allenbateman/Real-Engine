#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(UID uid) : Resource(uid)
{
	type = Type::Texture;
}

ResourceTexture::~ResourceTexture()
{
}
