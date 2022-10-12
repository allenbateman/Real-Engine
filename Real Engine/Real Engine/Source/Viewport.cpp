#include "Viewport.h"

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

	vMin.x += ImGui::GetWindowPos().x;
	vMin.y += ImGui::GetWindowPos().y;
	vMax.x += ImGui::GetWindowPos().x;
	vMax.y += ImGui::GetWindowPos().y;

	ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
	//app->renderer->OnResize(vMin.x, vMin.y, vMax.x, vMax.y);

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
