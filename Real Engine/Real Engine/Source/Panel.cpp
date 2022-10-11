#include "Panel.h"


Panel::Panel(bool startActive)
{
	active = startActive;
}

Panel::~Panel()
{
}

bool Panel::Init()
{
	return true;
}
bool Panel::Update()
{
	return true;
}

bool Panel::PostUpdate()
{
	return true;
}

bool Panel::CleanUp()
{
	return true;
}

void Panel::HandleEvents(Event* e)
{
}

