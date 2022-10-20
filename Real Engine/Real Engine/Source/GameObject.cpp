#include "GameObject.h"

void GameObject::Update()
{
}

void GameObject::Destroy()
{
}

Component* GameObject::CreateComponent(ComponentType type)
{
    Component* item = new Component();
    return item;
}
