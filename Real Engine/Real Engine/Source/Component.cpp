#include "Component.h"



Component::Component(componentType type)
{
	this->type = type;
}

Component::~Component()
{
}

void Component::Enable()
{
	bool active = true;
}

void Component::Update()
{
	
}

void Component::Disable()
{
	active = false;
}
