#pragma once
#include "Resource.h"
class ResourceFbx : public Resource
{
public :
    ResourceFbx(UID uid);
    ~ResourceFbx();

    unsigned int ChildCount;
    
};

