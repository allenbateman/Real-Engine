#include "GameObject.h"

void GameObject::Update()
{
}

Component* GameObject::CreateComponent(componentType type)
{
    Component* item = new Component(type);
    return item;
}
