#include "Viewport.h"
#include "FrameBuffer.h"
#include "EventSystem.h"
#include "Events.h"
Viewport::Viewport(bool isActive) : Panel(active)
{
}

Viewport::~Viewport()
{
}

bool Viewport::Init()
{

	return true;
}

bool Viewport::Update()
{
	// render your GUI
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
	ImGui::Begin("Camera Viewport");

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 vMin = ImGui::GetWindowContentRegionMin();
	ImVec2 vMax = ImGui::GetWindowContentRegionMax();
	ImVec2 availableSize;
	vMin.x += ImGui::GetWindowPos().x;
	vMin.y += ImGui::GetWindowPos().y;
	vMax.x += ImGui::GetWindowPos().x;
	vMax.y += ImGui::GetWindowPos().y;

	ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
	availableSize = ImGui::GetContentRegionAvail();

	const ImVec2& CurSize = ImGui::GetWindowViewport()->Size;
	if (LastSize.x != CurSize.x || LastSize.y != CurSize.y)
	{
		LastSize = CurSize;
		
		BroadCastEvent(new OnPanelResize(CurSize.x, CurSize.y));
		
	}
	ImGui::Image((ImTextureID)app->renderer->buffer.framebufferTexture, availableSize,ImVec2(0, 1), ImVec2(1, 0));
	

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
