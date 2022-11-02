#include "GameObject.h"

GameObject* GameObject::FindChild(Entity id)
{
	for (auto& child : childs)
	{
		if (child->id == id)
			return child; 
	}

	return nullptr;
}

void GameObject::Destroy()
{
	//if has childs destroy them too
}
