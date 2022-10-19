#include "Viewport.h"
#include "FrameBuffer.h"
#include "EventSystem.h"
#include "Events.h"
Viewport::Viewport(bool isActive) : Panel(active)
{
	name.Create("Camera Viewport");
}

Viewport::~Viewport()
{
}

bool Viewport::Init()
{

	active = true;
	window_flags = ImGuiWindowFlags_NoDocking;
	borderOffset = 0;
	return true;
}

bool Viewport::Update()
{
	// render your GUI
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
	
	if (ImGui::Begin("Camera Viewport"),NULL,window_flags)
	{
		ImGui::PopStyleVar();
		OnPanelHovered();
		ImVec2 availableSize;
		availableSize = ImGui::GetContentRegionAvail();
		if (LastSize.x != availableSize.x || LastSize.y != availableSize.y)
		{
			LastSize = availableSize;
			BroadCastEvent(new OnPanelResize(availableSize.x, availableSize.y));
		}
		ImGui::Image((ImTextureID)app->renderer->buffer.framebufferTexture, availableSize, ImVec2(0, 1), ImVec2(1, 0));

	}
	ImGui::End();

	return true;
}

bool Viewport::PostUpdate()
{
	return true;
}

bool Viewport::CleanUp()
{
	return true;
}

void Viewport::BroadCastEvent(Event* e)
{
	app->eventSystem->PostEvent(e);
}
