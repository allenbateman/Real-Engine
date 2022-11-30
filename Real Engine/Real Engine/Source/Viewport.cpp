#include "Viewport.h"

#include "Application.h"
#include "FrameBuffer.h"
#include "EventSystem.h"


Viewport::Viewport(int _id,bool isActive) : Panel(_id,isActive)
{
	name.Create("Camera Viewport");
}

Viewport::~Viewport()
{
}

void Viewport::Init()
{

	active = true;
	window_flags = ImGuiWindowFlags_NoDocking;
	borderOffset = 0;
}

void Viewport::Update()
{
	// render your GUI
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
	
	if (ImGui::Begin("Viewport"),NULL,window_flags)
	{

		OnHovered();
		OnResize();
		ImGui::Image((ImTextureID)app->renderer->editor.buffer.framebufferTexture, availableSize, ImVec2(0, 1), ImVec2(1, 0));
		
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

bool Viewport::CleanUp()
{
	Panel::CleanUp();
	return true;
}
