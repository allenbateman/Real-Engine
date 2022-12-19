#include "Resource.h"

Resource::Resource(UID id)
{
    uid = id;
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

const char* Resource::GetTypeChar()
{
	switch (type)
	{
	case Resource::Type::UNKNOWN:
		return "unknown";
	case Resource::Type::Texture:
		return "Texture";
	case Resource::Type::Material:
		return "Material";
	case Resource::Type::Mesh:
		return "Mesh";
	case Resource::Type::Fbx:
		return "Fbx";
	case Resource::Type::GObject:
		return "Gameobject";
	case Resource::Type::Shader:
		return "Shader";
	case Resource::Type::Scene:
		return "Scene";
	default:
		break;
	}
}
