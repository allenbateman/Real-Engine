#include "Resource.h"

Resource::Resource(UID id)
{
    uid = id;
}

Resource::~Resource()
{
}

void Resource::SetType(Resource::Type type)
{
   this->type = type;
}

Resource::Type Resource::GetType() const
{
    return type;
}

UID Resource::GetID() const
{
    return uid;
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