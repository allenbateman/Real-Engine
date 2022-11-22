#include "Resource.h"

Resource::Resource(UID id, Resource::Type type)
{
}

Resource::~Resource()
{
}

Resource::Type Resource::GetType(UID id)
{
    return Resource::Type();
}

UID Resource::GetID() const
{
    return UID();
}

const char* Resource::GetAssetFile() const
{
    return nullptr;
}

const char* Resource::GetLibraryFile() const
{
    return nullptr;
}

bool Resource::IsLoadedToMemory() const
{
    return false;
}

bool Resource::LoadToMemory()
{
    return false;
}

unsigned int Resource::GetRefereneCount() const
{
    return 0;
}

void Resource::Save() const
{
}

void Resource::Load() const
{
}

void Resource::UnLoad() const
{
}
