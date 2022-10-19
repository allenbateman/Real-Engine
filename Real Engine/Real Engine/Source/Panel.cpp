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

bool Panel::OnPanelHovered()
{
	if (ImGui::IsWindowHovered(0))
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();

		vMin.x += ImGui::GetWindowPos().x - borderOffset;
		vMin.y += ImGui::GetWindowPos().y - borderOffset;
		vMax.x += ImGui::GetWindowPos().x + borderOffset;
		vMax.y += ImGui::GetWindowPos().y + borderOffset;

		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, borderColor, 0, 0, borderOffset);

		return true;
	}
	return false;
}

void Panel::BroadCastEvent(Event* e)
{
}

void Panel::HandleEvents(Event* e)
{
}

