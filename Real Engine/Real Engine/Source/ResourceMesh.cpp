#include "ResourceMesh.h"


ResourceMesh::ResourceMesh(UID id) : Resource(id)
{

}
ResourceMesh::~ResourceMesh()
{

}

void ResourceMesh::Save() const
{
}

void ResourceMesh::Load() const
{
}

void ResourceMesh::UnLoad() const
{
}

Resource* ResourceMesh::Load(std::string UUID, std::ifstream& data)
{
	return nullptr;
}
