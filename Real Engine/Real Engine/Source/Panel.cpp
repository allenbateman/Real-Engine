#include "Panel.h"


Panel::Panel(bool startActive)
{
	active = startActive;
}

Panel::~Panel()
{
}

void Panel::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

}

void Panel::End()
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

bool Panel::CleanUp()
{
	return true;
}

void Panel::BroadCastEvent(Event* e)
{
}

void Panel::HandleEvents(Event* e)
{
}

