#include "Resource.h"

Resource::Resource(UID id)
{
    uid = id;
}

Resource::~Resource()
{
}

Resource::Type Resource::GetType(UID id)
{
    return type;
}

UID Resource::GetID() const
{
    return uid;
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
