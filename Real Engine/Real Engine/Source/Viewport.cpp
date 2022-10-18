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
		if (ImGui::IsWindowHovered(0))
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			ImVec2 vMax = ImGui::GetWindowContentRegionMax();
		
			vMin.x += ImGui::GetWindowPos().x;
			vMin.y += ImGui::GetWindowPos().y;
			vMax.x += ImGui::GetWindowPos().x;
			vMax.y += ImGui::GetWindowPos().y;

			ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(125, 125,125, 200));
		}
		ImVec2 availableSize;
		availableSize = ImGui::GetContentRegionAvail();
		const ImVec2& CurSize = ImGui::GetWindowViewport()->Size;
		if (LastSize.x != CurSize.x || LastSize.y != CurSize.y)
		{
			LastSize = CurSize;

			BroadCastEvent(new OnPanelResize(CurSize.x, CurSize.y));
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
