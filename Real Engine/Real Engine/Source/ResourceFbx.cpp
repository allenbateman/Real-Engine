#include "ResourceFbx.h"

ResourceFbx::ResourceFbx(UID uid): Resource(uid)
{
	type = Type::Fbx;
}

ResourceFbx::~ResourceFbx()
{
}

void ResourceFbx::Save() const
{
}

void ResourceFbx::Load() const
{
}

void ResourceFbx::UnLoad() const
{
}

Resource* ResourceFbx::Load(std::string UUID, std::ifstream& data)
{
	return nullptr;
}
