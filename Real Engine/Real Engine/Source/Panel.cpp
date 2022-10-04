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

void Panel::HandleEvenets(Event* e)
{
}
